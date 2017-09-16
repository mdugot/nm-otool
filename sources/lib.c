#include "nm.h"

int	pass_empty_bits(t_bin* bin)
{
	BYTE *b;
	int r;

	r = 0;
	while (dump_data(&b, bin, DESCRIPTION(1)))
	{
		if (*b)
		{
			rewind_bin(bin, 1);
			return r;
		}
		r++;
	}
	return -1;
}

void print_name(t_bin *bin, char *name)
{
	ft_printf("\n%s(%s):\n", bin->filename, name);
}

int	save_first(t_bin *bin)
{
	t_ar_header	*header;
	size_t size;

	if (!dump_data(&header, bin, DESCRIPTION(AR_HEADER_D)))
		return 0;
	size = get_ar_size(header);
	if (!dump_data(NULL, bin, DESCRIPTION(size)))
		return 0;
	return 1;
}

int	save_archive(t_bin *bin)
{
	t_ar_header	*header;
	size_t size;
	char *name;
	t_bin *sub;
	int	empty_bits;

	while (bin->cursor < bin->len)
	{
		if (!dump_data(&header, bin, DESCRIPTION(AR_HEADER_D)))
			return 0;
//		ft_putstr((char*)header);
		size = get_ar_size(header);
		if(!get_str(&name, bin, bin->cursor))
			return 0;
		if (!dump_data(NULL, bin, DESCRIPTION(ft_strlen(name))))
			return 0;
		if ((empty_bits = pass_empty_bits(bin)) < 0)
			return 0;
		size = size - empty_bits - ft_strlen(name);
		sub = sub_bin(bin, (size_t)size);
		if (!dump_data(NULL, bin, DESCRIPTION(size)))
			return 0;
		print_name(bin, name);
		magic_start(sub);
		ft_memdel((void*)&sub);
	}
	return 1;
}

int is_archive(t_bin *bin)
{
	char *tmp;

	tmp = (char*)(bin->begin + bin->cursor);
	if (strncmp(tmp, ARCHIVE_MAGIC, ft_strlen(ARCHIVE_MAGIC)))
		return 0;
	if (!dump_data(NULL, bin, DESCRIPTION(ft_strlen(ARCHIVE_MAGIC))))
		return 0;
	if (!save_first(bin))
		return 0;
	return save_archive(bin);
}

int get_ar_size(t_ar_header *header)
{
	int size;

	size = ft_atoi((char*)header->size);
//	ft_printf("size : %x\n", size);
	return size;
}
