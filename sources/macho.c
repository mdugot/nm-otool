#include "nm.h"

int is_macho_32(t_bin *bin)
{
	struct mach_header *header;
	if (check_magic_number(bin, MH_MAGIC))
	{
		if (!dump_data(&header, bin, sizeof(struct mach_header)))
			return 0;
		ft_printf("ft_nm: %s: 32 bits mach-o.\n", bin->filename);
		check_commands(bin, header->sizeofcmds, 32);
		return 1;
	}
	return 0;
}

int is_macho_64(t_bin *bin)
{
	struct mach_header_64 *header;
	if (check_magic_number(bin, MH_MAGIC_64))
	{
		if (!dump_data(&header, bin, sizeof(struct mach_header_64)))
			return 0;
		ft_printf("ft_nm: %s: 64 bits mach-o.\n", bin->filename);
		check_commands(bin, header->sizeofcmds, 64);
		return 1;
	}
	return 0;
}
