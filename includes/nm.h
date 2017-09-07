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

int is_macho_64(t_bin *bin);
int is_macho_32(t_bin *bin);
int check_magic_number(t_bin *bin, unsigned int magic);
void close_binary(t_bin *bin);
int open_binary(char *filename, t_bin *bin);
void rewind(t_bin *, size_t len);
void display_symbol_64(t_bin* bin);
void check_commands(t_bin* bin, size_t size, int cpu);
void rewind(t_bin *bin, size_t len);
int get_data(void *ad, t_bin *bin, size_t len, size_t offset);
int dump_data(void *ad, t_bin *bin, size_t len);
int get_str(void *ad, t_bin *bin, size_t offset);

#endif
