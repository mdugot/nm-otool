#include "nm.h"


t_usection	*new_usection(void *sec, int cpu)
{
	t_usection	*section;

	section = ft_memalloc(sizeof(t_usection));
	section->section = sec;
	section->cpu = cpu;
	return section;
}

void save_segment_64(t_bin *bin, struct load_command *lc, t_list **result)
{
	struct segment_command_64 *seg;
	struct section_64 *sect;
	size_t i;
	t_list *tmp;

	(void)lc;
//	ft_printf("there is a segment 64\n");
	if (!dump_data(&seg, bin, DESCRIPTION(SEGMENT_COMMAND_64_D)))
		return ;
	i = 0;
	while (i < seg->nsects)
	{
		if (!dump_data(&sect, bin, DESCRIPTION(SECTION_64_D)))
			return ;
		tmp = ft_lstnew_noalloc(new_usection(sect, 64), sizeof(t_usection));
		ft_lstadd_end(result, tmp);
		i++;
//		ft_printf("section name : %s\n", sect->sectname);
//		ft_printf("segment name : %s\n", sect->segname);
	}
}

void save_segment(t_bin *bin, struct load_command *lc, t_list **result)
{
	struct segment_command *seg;
	struct section *sect;
	size_t i;
	t_list *tmp;

	(void)lc;
//	ft_printf("there is a segment\n");
	if (!dump_data(&seg, bin, DESCRIPTION(SEGMENT_COMMAND_D)))
		return ;
	i = 0;
	while (i < seg->nsects)
	{
		if (!dump_data(&sect, bin, DESCRIPTION(SECTION_D)))
			return ;
		tmp = ft_lstnew_noalloc(new_usection(sect, 32), sizeof(t_usection));
		ft_lstadd_end(result, tmp);
		i++;
	}
}

t_list *save_commands(t_bin* bin, size_t size)
{
	struct load_command *lc;
	size_t i;
	t_list *tmp;
	t_list *result;
	t_bin *sub;

	i = 0;
	result = NULL;
	while (i < size) 
	{
		if (!dump_data(&lc, bin, DESCRIPTION(LOAD_COMMAND_D)))
			return result;
		rewind_bin(bin, sizeof(struct load_command));
		sub = sub_bin(bin, lc->cmdsize);
		if (!sub)
			return result;
		tmp = ft_lstnew_noalloc(sub, sizeof(t_bin));
		ft_lstadd_end(&result, tmp);
		i += lc->cmdsize;
		dump_data(NULL, bin, DESCRIPTION(lc->cmdsize));
	}
	return result;
}

t_list *save_usections(t_list *cmd)
{
	t_list *result;
	struct load_command *lc;
	t_bin *bin;

	result = NULL;
	while (cmd)
	{
		bin = (t_bin*)cmd->content;
		lc = (struct load_command*)bin->begin;
		if (lc->cmd == LC_SEGMENT)
			save_segment(bin, lc, &result);
		else if (lc->cmd == LC_SEGMENT_64)
			save_segment_64(bin, lc, &result);
		cmd = cmd->next;
	}
	return result;
}

t_list *save_all_symbol(t_list *cmd, int cpu, t_bin *bin)
{
	struct load_command *lc;
	t_bin *sbin;
	t_list *syms;

	syms = NULL;
	while (cmd)
	{
//		ft_printf("check command\n");
		sbin = (t_bin*)cmd->content;
		lc = (struct load_command*)sbin->begin;
//		ft_printf("command size: %llu.\n", lc->cmdsize);
//		ft_printf("command type: %#llx.\n", lc->cmd);
		if (lc->cmd == LC_SYMTAB && cpu == 64)
			save_symbol_64((t_bin*)cmd->content, bin, &syms);
		else if (lc->cmd == LC_SYMTAB && cpu == 32)
			save_symbol((t_bin*)cmd->content, bin, &syms);
		cmd = cmd->next;
	}
	return syms;
}
