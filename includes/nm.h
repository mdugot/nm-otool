#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include "libft.h"
# define BYTE unsigned char

typedef enum	e_endian
{
	BIG, LITTLE
}				t_endian;

typedef struct	s_bin
{
	char		*filename;
	int			fd;
	BYTE*		begin;
	BYTE*		cursor;
	size_t		len;
	t_endian	endian;
}				t_bin;

int is_macho_64(t_bin *bin);
int is_macho_32(t_bin *bin);
int check_magic_number(t_bin *bin, unsigned int magic);
void close_binary(t_bin *bin);
int open_binary(char *filename, t_bin *bin);
int dump_data(t_bin *bin, void *dest, size_t len);
void rewind(t_bin *, size_t len);
void display_symbol_64(t_bin* bin);
void check_commands(t_bin* bin, size_t size, int cpu);
void rewind(t_bin *bin, size_t len);
int cp_data(t_bin *bin, void *ad, size_t len, size_t offset);
int rcp_data(t_bin *bin, BYTE *dest, size_t len, BYTE *cursor);

#endif
