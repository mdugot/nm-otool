#include "nm.h"

char* get_section_name(void *ad)
{
	struct section* s;

	s = (struct section*)ad;
	return s->sectname;
}

char* get_section_name64(void *ad)
{
	struct section_64* s;

	s = (struct section_64*)ad;
	return s->sectname;
}

char* section_name(t_usection *section)
{
	if (section->cpu == 64)
		return get_section_name64(section->section);
	else
		return get_section_name(section->section);
}

void print_section_type(char* name, BYTE ext)
{
//	ft_printf("PRINT SECTION TYPE\n");
	if (!ft_strcmp(name, SECT_DATA))
		print_type_letter('d', ext);
	else if (!ft_strcmp(name, SECT_TEXT))
		print_type_letter('t', ext);
	else if (!ft_strcmp(name, SECT_BSS))
		print_type_letter('b', ext);
	else
		print_type_letter('s', ext);
}

void print_section(BYTE sect, BYTE ext, t_list *section)
{
	int i;

	i = 1;
	while (section)
	{
//		ft_printf("section name : %s\n", section_name(section->content));
		if (i == sect)
		{
			print_section_type(section_name(section->content), ext);
			return ;
		}
		i++;
		section = section->next;
	}
}
