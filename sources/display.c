#include "nm.h"

void display_value(unsigned long long ad)
{
	if (ad)
		ft_printf("%016llx ", ad);
	else
		ft_printf("                 ");
}

void display_symbol(t_usym *sym, t_list *section)
{
	if (is_debugging(sym->type))
		return ;
	display_value(sym->value);
	display_type(sym->type, sym->sect, section);
	ft_printf("%s\n", sym->str);
}

void display_all(t_list *sym, t_list *section)
{
	while (sym)
	{
		display_symbol((t_usym*)sym->content, section);
		sym = sym->next;
	}
}
