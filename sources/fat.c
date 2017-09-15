#include "nm.h"

int	cmp_bin(void *a1, void *a2)
{
	t_bin *b1;
	t_bin *b2;

	b1 = (t_bin*)a1;
	b2 = (t_bin*)a2;
	if (b1->cputype & CPU_ARCH_ABI64)
		return 1;
	return 0;
}

int	save_fat(t_bin* bin, t_list **list)
{
	struct fat_header *header;
	struct fat_arch *arch;
	unsigned int i;
	t_bin	*sub_bin;
	t_list	*tmp;

//	ft_printf("begin = %d\n", (int)bin->begin);
//	ft_printf("magic = %x\n", *((unsigned int*)bin->begin));
	if (check_magic_number(bin, FAT_MAGIC))
	{
//		ft_printf("IN\n");
		if (!dump_data(&header, bin, DESCRIPTION(FAT_HEADER_D)))
			return 0;
//		ft_printf("number = %u\n", header->nfat_arch);
		i = 0;
		while (i < header->nfat_arch)
		{
			if (!dump_data(&arch, bin, DESCRIPTION(FAT_ARCH_D)))
				return 0;
//			ft_printf("offset = %d\n", arch->offset);
//			ft_printf("size = %d\n", arch->size);
//			ft_printf("align = %8x\n", arch->align);
//			ft_printf("cpu type = %8x\n", arch->cputype & CPU_ARCH_ABI64);
//			ft_printf("cpu sub type = %b\n", arch->cpusubtype & CPU_SUBTYPE_LIB64);
//			ft_printf("sub magic = %x\n", *((unsigned int*)(bin->begin + arch->offset)));
			sub_bin = sub_bin_from_offset(bin, arch->size, arch->offset);
			tmp = ft_lstnew_noalloc(sub_bin, sizeof(t_bin));
			ft_lstadd_sorted(list, tmp, cmp_bin);
			i++;
		}
		return 1;
	}
	return 0;
}

int	is_fat(t_bin* bin)
{
	t_list *list;
	int r;

	list = NULL;
	if (!save_fat(bin, &list))
		return 0;
	r = magic_start((t_bin*)list->content);
	ft_lstfree(&list);
	return r;
}
