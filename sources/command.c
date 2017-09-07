#include "nm.h"

void check_commands(t_bin* bin, size_t size, int cpu)
{
	struct load_command lc;
	size_t i;

	i = 0;
	while (i < size) 
	{
		if (!dump_data(bin, &lc, sizeof(lc)))
			return ;
		rewind(bin, sizeof(lc));
		ft_printf("command size: %llu.\n", lc.cmdsize);
		ft_printf("command type: %#llx.\n", lc.cmd);
		i += lc.cmdsize;
		if (lc.cmd == LC_SYMTAB && cpu == 64)
			display_symbol_64(bin);
		else
			dump_data(bin, NULL, lc.cmdsize);
	}
}
