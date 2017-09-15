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
	bin->from = NULL;
	bin->cputype = 0;
	bin->cpusubtype = 0;
	bin->reverse_endian = 0;
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
	if ((bin->begin = mmap(0, bin->len, PROT_READ, MAP_PRIVATE, bin->fd, 0)) == MAP_FAILED ||
		(bin->mirror = mmap(0, bin->len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0)) == MAP_FAILED)
	{
		ft_printf_fd(2, "memory map of file '%s' failed\n", filename);
		return 0;
	}
	bin->cursor = 0;
	return 1;
}

void close_binary(t_bin *bin)
{
	munmap(bin->begin, bin->len);
	munmap(bin->mirror, bin->len);
}

void reverse_data(void *ad, size_t *s)
{
	while (*s)
	{
		reverse_byte(ad, *s);
		ad += *s;
		s++;
	}
	
}

size_t total_len(size_t *s)
{
	size_t len;

	len = 0;
	while (*s)
	{
		len += *s;
		s++;
	}
	return len;
}

void mirror_copy(t_bin * bin, size_t offset, size_t len, size_t *s)
{
	ft_memcpy(bin->mirror + offset, bin->begin + offset, len);
	if (bin->reverse_endian)
		reverse_data(bin->mirror + bin->cursor, s);
}

int dump_data(void *ad, t_bin *bin, size_t *s)
{
	void **dest;
	size_t len;

	len = total_len(s);
	dest = ad;
	if (bin->begin + bin->cursor + len > bin->begin + bin->len)
		return 0;
	if (ad)
	{
		mirror_copy(bin, bin->cursor, len, s);
		*dest = (void*)(bin->mirror + bin->cursor);
	}
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

int get_data(void *ad, t_bin *bin, size_t *s, size_t offset)
{
	void **dest;
	size_t len;

	len = total_len(s);
	dest = ad;
	if (!len || len + offset >bin->len)
		return 0;
	if (ad)
	{
		mirror_copy(bin, offset, len, s);
		*dest = (void*)(bin->mirror + offset);
	}
	return 1;
}

void rewind_bin(t_bin *bin, size_t len)
{
	bin->cursor -= len;
}

t_bin *sub_bin(t_bin *bin, size_t len)
{
	t_bin *sub;

	if (bin->cursor + len > bin->len)
		return NULL;
	sub = ft_memalloc(sizeof(t_bin));
	sub->filename = NULL;
	sub->fd = -1;
	sub->begin = bin->begin + bin->cursor;
	sub->mirror = bin->mirror + bin->cursor;
	sub->cursor = 0;
	sub->len = len;
	sub->cputype = bin->cputype;
	sub->cpusubtype = bin->cpusubtype;
	sub->reverse_endian = bin->reverse_endian;
	sub->from = bin;
	return sub;
}

t_bin *sub_bin_from_offset(t_bin *bin, size_t len, size_t offset)
{
	t_bin *sub;

	if (offset + len > bin->len)
		return NULL;
	sub = ft_memalloc(sizeof(t_bin));
	sub->filename = NULL;
	sub->fd = -1;
	sub->begin = bin->begin + offset;
	sub->mirror = bin->mirror + offset;
	sub->cursor = 0;
	sub->len = len;
	sub->cputype = bin->cputype;
	sub->cpusubtype = bin->cpusubtype;
	sub->reverse_endian = bin->reverse_endian;
	sub->from = bin;
	return sub;
}
