#include "nm.h"

void print_type_letter(char c, BYTE ext)
{
	if (ext)
		c = ft_toupper(c);
	ft_printf("%c ", c);
}

void display_type(BYTE n_type, BYTE n_sect, t_list *section, uint64_t n_value)
{
	BYTE stab;
	BYTE pext;
	BYTE type;
	BYTE ext;

	stab = n_type & N_STAB;
	pext = n_type & N_PEXT;
	type = n_type & N_TYPE;
	ext = n_type & N_EXT;

//	ft_printf("type %#hhx sect %#hhx\n", n_type, n_sect);
//	ft_printf("STAB %#hhx PEXT %#hhx TYPE %#hhx EXT %#hhx\n", stab, pext, type, ext);
	
	if (stab)
		print_type_letter('-', ext);
	else if ((type & N_TYPE) == N_ABS)
		print_type_letter('a', ext);
	else if ((type & N_TYPE) == N_PBUD)
		print_type_letter('u', ext);
	else if ((type & N_TYPE) == N_INDR)
		print_type_letter('i', ext);
	else if ((type & N_TYPE) == N_SECT)
		print_section(n_sect, ext, section);
	else if ((type & N_TYPE) == N_UNDF)
	{
		if (n_value != 0)
			print_type_letter('c', ext);
		else
			print_type_letter('u', ext);
	}
	else
		print_type_letter('?', ext);
	
}

int is_debugging(BYTE n_type)
{
	return (n_type & N_STAB);
}
