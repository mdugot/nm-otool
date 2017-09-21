#include "nm.h"

void print_invalid(char *filename)
{
	if (!ft_strcmp(TARGET, NM))
		ft_printf_fd(2, "ft_nm: %s: The file was not recognized as a valid object file.\n", filename);
	else
		ft_printf_fd(2, "%s: is not an object file\n", filename);
}

void display_name_list(char *filename, int *result)
{
	t_bin bin;

	if (!open_binary(filename, &bin))
	{
		*result = 1;
		return;
	}
	if (bin.len <= 0 || !magic_start(&bin))
	{
		print_invalid(filename);
		*result = 1;
	}
	close_binary(&bin);
}

int main(int argc, char **argv)
{
	int i;
	int result;

	f_argc(argc);
	result = 0;
	// ft_printf("target : %s\n", TARGET);
	if (argc < 2)
	{
		if (!ft_strcmp(TARGET, OTOOL))
		{
			ft_printf("error: ft_otool: at least one file must be specified\n");
			return 1;
		}
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
