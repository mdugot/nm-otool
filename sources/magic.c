#include "nm.h"

void reverse_endian(BYTE* bytes, size_t len)
{
	size_t i = 0;
	BYTE tmp;

	while (i < len / 2)
	{
		tmp = bytes[i];
		bytes[i] = bytes[len - i - 1];
		bytes[len - i - 1] = tmp;
		i++;
	}
}

int check_magic_little(t_bin *bin, BYTE magic[4])
{
	reverse_endian(magic, 4);
	return ((int)*(bin->begin) == (int)*magic);
}

int check_magic_big(t_bin *bin, BYTE magic[4])
{
	return ((int)*(bin->begin) == (int)*magic);
}

int check_magic_number(t_bin *bin, unsigned int magic)
{
	BYTE bmagic[4];

	*bmagic = magic;
	if (check_magic_big(bin, bmagic))
		return 1;
	if (check_magic_little(bin, bmagic))
		return 1;
	return 0;
}
