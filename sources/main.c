#include "nm.h"

void display_name_list(char *filename, int *result)
{
	t_bin bin;

	if (!open_binary(filename, &bin))
	{
		*result = 1;
		return;
	}
	if (magic_start(&bin))
		return ;
	ft_printf_fd(2, "ft_nm: %s: The file was not recognized as a valid object file.\n", filename);
	*result = 1;
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
