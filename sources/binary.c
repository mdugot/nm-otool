#include "nm.h"

int get_len(t_bin *bin)
{
	struct stat st;
	if (fstat(bin->fd, &st) < 0)
		return 0;
	bin->len = st.st_size;
	return 1;
}

int open_binary(char *filename, t_bin *bin)
{
	bin->filename = filename;
	bin->fd = open(filename, O_RDONLY);
	if (bin->fd < 0)
	{
		ft_printf_fd(2, "can not open '%s'\n", filename);
		return 0;
	}
	if (!get_len(bin))
	{
		ft_printf_fd(2, "can not get stats of '%s'\n", filename);
		return 0;
	}
	if ((bin->begin = mmap(0, bin->len, PROT_READ, MAP_PRIVATE, bin->fd, 0)) == MAP_FAILED)
	{
		ft_printf_fd(2, "memory map of file '%s' failed\n", filename);
		return 0;
	}
	bin->endian = BIG;
	bin->cursor = bin->begin;
	return 1;
}

void close_binary(t_bin *bin)
{
	munmap(bin->begin, bin->len);
}

int rdump_data(t_bin *bin, BYTE *dest, size_t len)
{
	size_t i;
	i = 0;
	while (i < len)
	{
		dest[len - 1 - i] = *(bin->cursor);
		bin->cursor += 1;
		i++;
	}
	return 1;
}

int dump_data(t_bin *bin, void *ad, size_t len)
{
	size_t i;
	BYTE *dest;

	dest = (BYTE*)ad;
	if (bin->cursor + len > bin->begin + bin->len)
		return 0;
	if (bin->endian == LITTLE && dest)
		return rdump_data(bin, dest, len);
	i = 0;
	while (i < len)
	{
		if (dest)
			dest[i] = *(bin->cursor);
		bin->cursor += 1;
		i++;
	}
	return 1;
}

int rcp_data(t_bin *bin, BYTE *dest, size_t len, BYTE *cursor)
{
	size_t i;

	i = 0;
	cursor = bin->cursor;
	while (i < len)
	{
		dest[len - 1 - i] = *cursor;
		cursor += 1;
		i++;
	}
	return 1;
}

int cp_data(t_bin *bin, void *ad, size_t len, size_t offset)
{
	size_t i;
	BYTE *dest;
	BYTE *cursor;

	dest = (BYTE*)ad;
	if (len + offset > (size_t)(bin->begin + bin->len))
		return 0;
	cursor = bin->begin + offset;
	if (bin->endian == LITTLE && dest)
		return rcp_data(bin, dest, len, cursor);
	i = 0;
	while (i < len)
	{
		if (dest)
			dest[i] = *cursor;
		cursor += 1;
		i++;
	}
	return 1;
}

void rewind(t_bin *bin, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		bin->cursor -= 1;
		i++;
	}
}
