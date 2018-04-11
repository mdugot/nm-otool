# nm-otool
Reproduction of the nm and otool commands.

Ft_nm will display the name list (symbol table) of each object file in the argument list.  
If an argument is an archive, a listing for each object file in the archive will be produced. 

>./ft_nm /bin/cat /usr/lib/libc.dylib

Ft_otool will display the contents of the (__TEXT,__text) section of each object file in the argument list.

>./ft_otool /bin/echo
