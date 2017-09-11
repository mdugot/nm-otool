#include "nm.h"

void display_symbol(t_bin* cmd, t_bin *bin)
{
	struct symtab_command *sc;
	struct nlist *nl;
	char *str;
	size_t i;

	if (!dump_data(&sc, cmd, sizeof(struct symtab_command)))
		return ;
	i = 0;
	while (i < sc->nsyms)
	{
		if (!get_data(&nl, bin, sizeof(struct nlist), sc->symoff + i * sizeof(struct nlist)))
			return ;
//		str = (void*)bin->begin + sc->stroff + nl->n_un.n_strx;
		if (get_str(&str, bin, sc->stroff + nl->n_un.n_strx)) 
		{
			display_type(nl->n_type, nl->n_sect);
			ft_printf("%s\n", str);
		}
		i++;
	}
}

void display_symbol_64(t_bin* cmd, t_bin *bin)
{
	struct symtab_command *sc;
	struct nlist_64 *nl;
	char *str;
	size_t i;

	if (!dump_data(&sc, cmd, sizeof(struct symtab_command)))
		return ;
	i = 0;
	while (i < sc->nsyms)
	{
		ft_printf("display symbol\n");
		if (!get_data(&nl, bin, sizeof(struct nlist_64), sc->symoff + i * sizeof(struct nlist_64)))
			return ;
//		str = (void*)bin->begin + sc->stroff + nl->n_un.n_strx;
		if (get_str(&str, bin, sc->stroff + nl->n_un.n_strx)) 
		{
			display_type(nl->n_type, nl->n_sect);
			ft_printf("%s\n", str);
		}
		i++;
	}
}
