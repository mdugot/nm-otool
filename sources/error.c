#include "nm.h"

void print_error(char *filename, char *nm_str, char *o1, char *o2)
{
	if (!ft_strcmp(TARGET, NM))
		ft_printf_fd(2, "ft_nm: %s: %s\n", filename, nm_str);
	else
		ft_printf_fd(2, "error: ft_otool: %s: %s (%s)\n", o1, filename, o2);
}

void check_errno(char *filename)
{
	if (errno == EACCES)
	{
		print_error(filename,
			"Permission denied.",
			"can't open file",
			"Permission denied");
	}
	else
	{
		print_error(filename,
			"No such file or directory.",
			"can't open file",
			"No such file or directory");
	}
}

int check_file_stat(t_bin *bin, struct stat *st)
{
	if (S_ISDIR(st->st_mode))
	{
		print_error(bin->filename,
			"Is a directory.",
			"can't map file",
			"Invalid argument");
		return 0;
	}
	return 1;
}
