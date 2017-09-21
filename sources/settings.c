#include "nm.h"

int	f_argc(int v)
{
	static int argc = -1;

	if (v > 0)
		argc = v;
	return argc;
}
