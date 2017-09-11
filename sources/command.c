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
	ft_printf("there is a segment 64\n");
	if (!dump_data(&seg, bin, sizeof(struct segment_command_64)))
		return ;
	i = 0;
	while (i < seg->nsects)
	{
		if (!dump_data(&sect, bin, sizeof(struct section_64)))
			return ;
		tmp = ft_lstnew_noalloc(new_usection(sect, 64), sizeof(t_usection));
		ft_lstadd(result, tmp);
		i++;
	}
}

void save_segment(t_bin *bin, struct load_command *lc, t_list **result)
{
	(void)lc;
	(void)bin;
	(void)result;
	ft_printf("there is a segment\n");
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
		if (!dump_data(&lc, bin, sizeof(struct load_command)))
			return result;
		rewind(bin, sizeof(struct load_command));
		sub = sub_bin(bin, lc->cmdsize);
		if (!sub)
			return result;
		tmp = ft_lstnew_noalloc(sub, sizeof(t_bin));
		ft_lstadd(&result, tmp);
		i += lc->cmdsize;
		dump_data(NULL, bin, lc->cmdsize);
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

void check_commands(t_list *cmd, int cpu, t_bin *bin)
{
	struct load_command *lc;
	t_bin *sbin;

	while (cmd)
	{
		ft_printf("check command\n");
		sbin = (t_bin*)cmd->content;
		lc = (struct load_command*)sbin->begin;
//		ft_printf("command size: %llu.\n", lc->cmdsize);
//		ft_printf("command type: %#llx.\n", lc->cmd);
		if (lc->cmd == LC_SYMTAB && cpu == 64)
			display_symbol_64((t_bin*)cmd->content, bin);
		else if (lc->cmd == LC_SYMTAB && cpu == 32)
			display_symbol((t_bin*)cmd->content, bin);
		cmd = cmd->next;
	}
}
