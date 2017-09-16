#include "nm.h"

char* get_segment_name(void *ad)
{
	struct section* s;

	s = (struct section*)ad;
	return s->segname;
}

char* get_segment_name64(void *ad)
{
	struct section_64* s;

	s = (struct section_64*)ad;
	return s->segname;
}

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

char* segment_name(t_usection *section)
{
	if (section->cpu == 64)
		return get_segment_name64(section->section);
	else
		return get_segment_name(section->section);
}

void print_section_type(char* seg, char* sect, BYTE ext)
{
//	ft_printf("section name len : %d\n", ft_strlen(name));
	if (!ft_strcmp(seg, SEG_DATA) && !ft_strcmp(sect, SECT_DATA))
		print_type_letter('d', ext);
	else if (!ft_strcmp(seg, SEG_TEXT) && !ft_strcmp(sect, SECT_TEXT))
		print_type_letter('t', ext);
	else if (!ft_strcmp(seg, SEG_DATA) && !ft_strcmp(sect, SECT_BSS))
		print_type_letter('b', ext);
	else
		print_type_letter('s', ext);
}

void print_section(BYTE sect, BYTE ext, t_list *section)
{
	int i;

	i = 1;
//	ft_printf("section index : %d\n", sect);
	while (section)
	{
//		ft_printf("section name : %s\n", section_name(section->content));
		if (i == sect)
		{
			print_section_type(segment_name(section->content), section_name(section->content), ext);
			return ;
		}
		i++;
		section = section->next;
	}
	print_type_letter('s', ext);
}
