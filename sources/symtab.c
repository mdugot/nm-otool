#include "nm.h"

void display_symbol_64(t_bin* bin)
{
	struct symtab_command sc;
	struct nlist_64 nl;
	char *str;
	size_t i;

	if (!dump_data(bin, &sc, sizeof(sc)))
		return ;
	i = 0;
	while (i < sc.nsyms)
	{
		if (!cp_data(bin, &nl, sizeof(nl), sc.symoff + i * sizeof(nl)))
			return ;
		str = (void*)bin->begin + sc.stroff + nl.n_un.n_strx;
		ft_printf("%s\n", str);
		i++;
	}
}
