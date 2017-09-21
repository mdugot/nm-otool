#include "nm.h"

void print_filename(t_bin *bin)
{
	if (!ft_strcmp(TARGET, NM))
		ft_printf("\n%s:\n", bin->filename);
	else
		ft_printf("%s:\n", bin->filename);
}

void analyze_cmd(t_list *cmds, t_bin *bin)
{
	t_list *sections;
	t_list *syms;

	if (bin->filename && f_argc(-1) > 2)
		print_filename(bin);
	sections = save_usections(cmds);
	syms = save_all_symbol(cmds, 64, bin);
	if (!ft_strcmp(NM, TARGET))
		display_all(syms, sections, 64);
	if (!ft_strcmp(OTOOL, TARGET))
		otool(sections, bin);
	ft_lstfree(&sections);
	ft_lstfree(&syms);
}

int is_macho_32(t_bin *bin)
{
	struct mach_header *header;
	t_list *cmds;

	if (check_magic_number(bin, MH_MAGIC))
	{
		if (!dump_data(&header, bin, DESCRIPTION(MACH_HEADER_D)))
			return 0;
//		ft_printf("ft_nm: %s: 32 bits mach-o.\n", bin->filename);
		cmds = save_commands(bin, header->sizeofcmds);
		if (!cmds)
			return 0;
		analyze_cmd(cmds, bin);
		ft_lstfree(&cmds);
		return 1;
	}
	return 0;
}

int is_macho_64(t_bin *bin)
{
	struct mach_header_64 *header;
	t_list *cmds;

	if (check_magic_number(bin, MH_MAGIC_64))
	{
		if (!dump_data(&header, bin, DESCRIPTION(MACH_HEADER_64_D)))
			return 0;
		bin->cputype = header->cputype;
		bin->cpusubtype = header->cpusubtype;
//		ft_printf("ft_nm: %s: 64 bits mach-o.\n", bin->filename);
		cmds = save_commands(bin, header->sizeofcmds);
		if (!cmds)
			return 0;
		analyze_cmd(cmds, bin);
		ft_lstfree(&cmds);
		return 1;
	}
	return 0;
}
