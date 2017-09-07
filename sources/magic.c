#include "nm.h"

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
/*	if (check_magic_little(bin, bmagic))
	{
		ft_printf("#RLITTLE ENDIAN#N\n");
		bin->endian = LITTLE;
		return 1;
	}*/
	return 0;
}
