#ifndef NM_H
# define NM_H

# include <sys/mman.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include "libft.h"
# define BYTE unsigned char

# define DESCRIPTION(X) (size_t[]){X, 0}
# define SEGMENT_COMMAND_64_D \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(char) * 16, \
  sizeof(uint64_t), \
  sizeof(uint64_t), \
  sizeof(uint64_t), \
  sizeof(uint64_t), \
  sizeof(vm_prot_t), \
  sizeof(vm_prot_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t)
# define SEGMENT_COMMAND_D \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(char) * 16, \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(vm_prot_t), \
  sizeof(vm_prot_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t)
# define SECTION_D \
  sizeof(char) * 16, \
  sizeof(char) * 16, \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t)
# define SECTION_64_D \
  sizeof(char) * 16, \
  sizeof(char) * 16, \
  sizeof(uint64_t), \
  sizeof(uint64_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t)
# define LOAD_COMMAND_D \
  sizeof(uint32_t), \
  sizeof(uint32_t)
# define FAT_HEADER_D \
  sizeof(uint32_t), \
  sizeof(uint32_t)
# define FAT_ARCH_D \
  sizeof(cpu_type_t), \
  sizeof(cpu_subtype_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t)
# define MACH_HEADER_D \
  sizeof(uint32_t), \
  sizeof(cpu_type_t), \
  sizeof(cpu_subtype_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t)
# define MACH_HEADER_64_D \
  sizeof(uint32_t), \
  sizeof(cpu_type_t), \
  sizeof(cpu_subtype_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t)
# define SYMTAB_COMMAND_D \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t), \
  sizeof(uint32_t)
# define NLIST_D \
  sizeof(char*), \
  sizeof(uint8_t), \
  sizeof(uint8_t), \
  sizeof(int16_t), \
  sizeof(uint32_t)
# define NLIST_64_D \
  sizeof(uint32_t), \
  sizeof(uint8_t), \
  sizeof(uint8_t), \
  sizeof(uint16_t), \
  sizeof(uint64_t)
# define AR_HEADER_D \
  16, \
  12, \
  6, \
  6, \
  8, \
  10, \
  2

# define ARCHIVE_MAGIC "!<arch>\n"


typedef struct	s_ar_header
{
	BYTE		id[16];
	BYTE		timestamp[12];
	BYTE		owner[6];
	BYTE		group[6];
	BYTE		mode[8];
	BYTE		size[10];
	BYTE		end[2];
}				t_ar_header;


typedef struct	s_bin
{
	struct s_bin	*from;
	int			cputype;
	int			cpusubtype;
	char		*filename;
	int			fd;
	BYTE*		begin;
	BYTE*		mirror;
	size_t		cursor;
	size_t		len;
	int			reverse_endian;
}				t_bin;

typedef struct	s_usection
{
	void		*section;
	int			cpu;
}				t_usection;

typedef struct	s_usym
{
	uint64_t	value;
	BYTE		type;
	BYTE		sect;
	char*		str;
	
}				t_usym;

int is_macho_64(t_bin *bin);
int is_macho_32(t_bin *bin);
int check_magic_number(t_bin *bin, unsigned int magic);
void close_binary(t_bin *bin);
int open_binary(char *filename, t_bin *bin);
void save_symbol_64(t_bin* cmd, t_bin* bin, t_list **syms);
void save_symbol(t_bin* cmd, t_bin* bin, t_list **syms);
void rewind_bin(t_bin *bin, size_t len);
int get_data(void *ad, t_bin *bin, size_t *s, size_t offset);
int dump_data(void *ad, t_bin *bin, size_t *s);
int get_str(void *ad, t_bin *bin, size_t offset);
void display_type(BYTE type, BYTE n_sect, t_list *section, uint64_t n_value);
t_list *save_usections(t_list *cmd);
t_list *save_commands(t_bin* bin, size_t size);
t_bin *sub_bin(t_bin *bin, size_t len);
t_list *save_all_symbol(t_list *cmd, int cpu, t_bin *bin);
void print_type_letter(char c, BYTE ext);
void print_section(BYTE sect, BYTE ext, t_list *section);
void display_all(t_list *sym, t_list *section, int cpu);
int is_debugging(BYTE n_type);
int magic_start(t_bin *bin);
int	is_fat(t_bin* bin);
void reverse_byte(void *ad, size_t size);
t_bin *sub_bin_from_offset(t_bin *bin, size_t len, size_t offset);
int is_archive(t_bin *bin);
int get_ar_size(t_ar_header *header);

#endif
