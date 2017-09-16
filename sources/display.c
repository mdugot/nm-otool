#include "nm.h"

void display_value(unsigned long long ad, BYTE sect, int cpu)
{
	int w;

	w = (cpu == 64 ? 16 : 8);
	if (sect)
		ft_printf("%0*llx ", w, ad);
	else
		ft_printf("%*s", w + 1, "");
}

void display_symbol(t_usym *sym, t_list *section, int cpu)
{
	if (is_debugging(sym->type))
		return ;
	display_value(sym->value, sym->sect, cpu);
	display_type(sym->type, sym->sect, section, sym->value);
	ft_printf("%s\n", sym->str);
}

void display_all(t_list *sym, t_list *section, int cpu)
{
	while (sym)
	{
		display_symbol((t_usym*)sym->content, section, cpu);
		sym = sym->next;
	}
}
