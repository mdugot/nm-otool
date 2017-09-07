#include "nm.h"

void display_symbol_64(t_bin* bin)
{
	struct symtab_command *sc;
	struct nlist_64 *nl;
	char *str;
	size_t i;

	if (!dump_data(&sc, bin, sizeof(struct symtab_command)))
		return ;
	i = 0;
	while (i < sc->nsyms)
	{
		if (!get_data(&nl, bin, sizeof(struct nlist_64), sc->symoff + i * sizeof(struct nlist_64)))
			return ;
//		str = (void*)bin->begin + sc->stroff + nl->n_un.n_strx;
		if (get_str(&str, bin, sc->stroff + nl->n_un.n_strx)) 
			ft_printf("%s\n", str);
		i++;
	}
}
