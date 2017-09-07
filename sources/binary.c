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
	bin->cursor = bin->begin;
	return 1;
}

void close_binary(t_bin *bin)
{
	munmap(bin->begin, bin->len);
}

int dump_data(void *ad, t_bin *bin, size_t len)
{
	void **dest;

	dest = ad;
	if (bin->cursor + len > bin->begin + bin->len)
		return 0;
	if (ad)
		*dest = (void*)bin->cursor;
	bin->cursor += len;
	return 1;
}

int get_str(void *ad, t_bin *bin, size_t offset)
{
	void **dest;
	char *test;
	size_t i;

	dest = ad;
	if (offset >= bin->len)
		return 0;
	if (ad)
		*dest = (void*)(bin->begin + offset);
	test = *dest;
	i = 0;
	while (test[i])
	{
		i++;
		if (offset + i >= bin->len)
			return 0;
	}
	return 1;
}

int get_data(void *ad, t_bin *bin, size_t len, size_t offset)
{
	void **dest;

	dest = ad;
	if (!len || len + offset >bin->len)
		return 0;
	if (ad)
		*dest = (void*)(bin->begin + offset);
	return 1;
}

void rewind(t_bin *bin, size_t len)
{
	bin->cursor -= len;
}
