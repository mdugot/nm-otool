#include "nm.h"

void reverse_byte(void *ad, size_t size)
{
	size_t i;
	BYTE *bytes;
	BYTE tmp;

	bytes = (BYTE*)ad;
	i = 0;
	while (i < size / 2)
	{
		tmp = bytes[i];
		bytes[i] = bytes[size - i - 1];
		bytes[size - i - 1] = tmp;
		i++;
	}
}

int check_magic_big(t_bin *bin, BYTE magic[4])
{
//	ft_printf("big = %x\n", *((unsigned int*)magic));
	return (*((unsigned int*)(bin->begin + bin->cursor)) == *((unsigned int*)magic));
}

int check_magic_little(t_bin *bin, BYTE magic[4])
{
	reverse_byte(magic, 4);
//	ft_printf("little = %x\n", *((unsigned int*)magic));
	return check_magic_big(bin, magic);
}

int check_magic_number(t_bin *bin, unsigned int magic)
{
	BYTE bmagic[4];

//	ft_printf("MAGIC NUMBER = %x\n", magic);
	*((unsigned int*)bmagic) = magic;
//	ft_printf("BMAGIC NUMBER = %x\n", *((unsigned int*)bmagic));
	if (check_magic_big(bin, bmagic))
	{
//		ft_printf("#BBIG ENDIAN#N\n");
		bin->reverse_endian = 0;
		return 1;
	}
	if (check_magic_little(bin, bmagic))
	{
//		ft_printf("#RLITTLE ENDIAN#N\n");
		bin->reverse_endian = 1;
		return 1;
	}
	return 0;
}

int magic_start(t_bin *bin)
{
//	ft_printf("check magic = %x\n", *((unsigned int*)(bin->begin + bin->cursor)));
	if (is_macho_32(bin))
		return 1;
	if (is_macho_64(bin))
		return 1;
	if (is_fat(bin))
		return 1;
//	ft_printf("format not recognize\n");
	return 0;
}
