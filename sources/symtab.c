#include "nm.h"

int		cmp_sym(void *a1, void *a2)
{
	t_usym*	s1;
	t_usym*	s2;
	int r;

	s1 = (t_usym*)a1;
	s2 = (t_usym*)a2;
	r = ft_strcmp(s1->str, s2->str);
	if (r)
		return r;
	return s1->value > s2->value;
}

void	add_sym(uint64_t value, BYTE type, BYTE sect, char* str, t_list **list)
{
	t_usym*	newsym;
	t_list*	tmp;

	newsym = ft_memalloc(sizeof(t_usym));
	newsym->value = value;
	newsym->type = type;
	newsym->sect = sect;
	newsym->str = str;
	tmp = ft_lstnew_noalloc(newsym, sizeof(t_usym));
	ft_lstadd_sorted(list, tmp, cmp_sym);
}

void save_symbol(t_bin* cmd, t_bin *bin, t_list **syms)
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
			add_sym(nl->n_value, nl->n_type, nl->n_sect, str, syms);
		i++;
	}

}

void save_symbol_64(t_bin* cmd, t_bin *bin, t_list **syms)
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
//		ft_printf("display symbol\n");
		if (!get_data(&nl, bin, sizeof(struct nlist_64), sc->symoff + i * sizeof(struct nlist_64)))
			return ;
//		str = (void*)bin->begin + sc->stroff + nl->n_un.n_strx;
		if (get_str(&str, bin, sc->stroff + nl->n_un.n_strx)) 
			add_sym(nl->n_value, nl->n_type, nl->n_sect, str, syms);
		i++;
	}
}
