#include "nm.h"

void* get_section_adress(t_usection *section)
{
	struct section* s;
	struct section_64* s64;

	if (section->cpu == 64)
	{
		s64 = (struct section_64*)section->section;
		return (void*)s64->addr;
	}
	s = (struct section*)section->section;
	return (void*)(uintptr_t)s->addr;
}

uint32_t get_section_offset(t_usection *section)
{
	struct section* s;
	struct section_64* s64;

	if (section->cpu == 64)
	{
		s64 = (struct section_64*)section->section;
		return s64->offset;
	}
	s = (struct section*)section->section;
	return s->offset;
}

size_t get_section_size(t_usection *section)
{
	struct section* s;
	struct section_64* s64;

	if (section->cpu == 64)
	{
		s64 = (struct section_64*)section->section;
		return s64->size;
	}
	s = (struct section*)section->section;
	return s->size;
}

void	display_text_memory(size_t size, BYTE *ad, int w, BYTE *begin)
{
	size_t i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		ft_printf("%0*llx", w, begin + i);
		while (j < 16 && i < size)
		{
			ft_printf(" %02hhx", ad[i]);
			j++;
			i++;
		}
		ft_printf("\n");
	}
}

void	display_text(t_usection *section, t_bin *bin)
{
	size_t size;
	BYTE *ad;
	int w;
	BYTE *begin;

	w = (section->cpu == 64 ? 16 : 8);
	ft_printf("(__TEXT,__text) section\n");
	size = get_section_size(section);
	begin = get_section_adress(section);
	if (!get_bytes(&ad, bin, DESCRIPTION(size), get_section_offset(section)))
		return ;
//	ft_printf("addr : %0*llx\n", w, get_section_adress(section));
//	ft_printf("offset : %0*x\n", w, get_section_offset(section));
	display_text_memory(size, ad, w, begin);
}

int is_text(void* ad)
{
	char *segname;
	char *sectname;

	segname = segment_name(ad);
	sectname = section_name(ad);
	if (ft_strcmp(segname, SEG_TEXT))
		return 0;
	if (ft_strcmp(sectname, SECT_TEXT))
		return 0;
	return 1;
}

void	otool(t_list *section, t_bin *bin)
{
	while (section)
	{
		if (is_text(section->content))
		{
			display_text(section->content, bin);
			return ;
		}
		section = section->next;
	}
}
