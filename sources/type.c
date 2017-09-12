#include "nm.h"

void print_type_letter(char c, BYTE ext)
{
	if (ext)
		c = ft_toupper(c);
	ft_printf("%c ", c);
}

void display_type(BYTE n_type, BYTE n_sect, t_list *section)
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
	
	if (type == N_ABS)
		print_type_letter('a', ext);
	else if (type == N_SECT)
		print_section(n_sect, ext, section);
	else if (type == N_UNDF)
		print_type_letter('u', ext);
	else
		print_type_letter('?', ext);
	
}
