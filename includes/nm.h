#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "libft.h"
# define BYTE unsigned char

typedef struct	s_bin
{
	char		*filename;
	int			fd;
	BYTE*		begin;
	BYTE*		cursor;
	size_t		len;
}				t_bin;

typedef struct	s_usection
{
	void		*section;
	int			cpu;
}				t_usection;

typedef struct	s_usym
{
	uint32_t	value;
	BYTE		type;
	BYTE		sect;
	char*		str;
	
}				t_usym;

int is_macho_64(t_bin *bin);
int is_macho_32(t_bin *bin);
int check_magic_number(t_bin *bin, unsigned int magic);
void close_binary(t_bin *bin);
int open_binary(char *filename, t_bin *bin);
void rewind(t_bin *, size_t len);
void save_symbol_64(t_bin* cmd, t_bin* bin, t_list **syms);
void save_symbol(t_bin* cmd, t_bin* bin, t_list **syms);
void rewind(t_bin *bin, size_t len);
int get_data(void *ad, t_bin *bin, size_t len, size_t offset);
int dump_data(void *ad, t_bin *bin, size_t len);
int get_str(void *ad, t_bin *bin, size_t offset);
void display_type(BYTE type, BYTE n_sect, t_list *section);
t_list *save_usections(t_list *cmd);
t_list *save_commands(t_bin* bin, size_t size);
t_bin *sub_bin(t_bin *bin, size_t len);
t_list *save_all_symbol(t_list *cmd, int cpu, t_bin *bin);
void print_type_letter(char c, BYTE ext);
void print_section(BYTE sect, BYTE ext, t_list *section);
void display_all(t_list *sym, t_list *section);

#endif
