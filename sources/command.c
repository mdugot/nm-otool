#include "nm.h"

void check_commands(t_bin* bin, size_t size, int cpu)
{
	struct load_command *lc;
	size_t i;

	i = 0;
	while (i < size) 
	{
		if (!dump_data(&lc, bin, sizeof(struct load_command)))
			return ;
		rewind(bin, sizeof(struct load_command));
//		ft_printf("command size: %llu.\n", lc->cmdsize);
//		ft_printf("command type: %#llx.\n", lc->cmd);
		i += lc->cmdsize;
		if (lc->cmd == LC_SYMTAB && cpu == 64)
			display_symbol_64(bin);
		else if (lc->cmd == LC_SYMTAB && cpu == 32)
			display_symbol(bin);
		else
			dump_data(NULL, bin, lc->cmdsize);
	}
}
