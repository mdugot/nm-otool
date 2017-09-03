#include <unistd.h>
#include "libft.h"

void display_name_list(char *filename, int *result)
{
	(void)result;
	ft_printf("#R%s#N\n", filename);
}

int main(int argc, char **argv)
{
	int i;
	int result;

	result = 0;
	if (argc < 2)
	{
		display_name_list("a.out", &result);
		return result;
	}
	i = 1;
	while (i < argc)
	{
		display_name_list(argv[i], &result);
		i++;
	}
	return result;
}
