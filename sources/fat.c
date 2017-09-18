#include "nm.h"

int	cmp_bin(void *a1, void *a2)
{
	t_bin *b1;
	t_bin *b2;

	b1 = (t_bin*)a1;
	b2 = (t_bin*)a2;
	if (b1->cputype == MACHINE_CPU)
		return 0;
	return 1;
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
//			ft_printf("x86 64b = %8x\n", MACHINE_CPU);
//			ft_printf("cpu type = %8x\n", arch->cputype);
//			ft_printf("cpu sub type = %b\n", arch->cpusubtype);
//			ft_printf("sub magic = %x\n", *((unsigned int*)(bin->begin + arch->offset)));
			sub_bin = sub_bin_from_offset(bin, arch->size, arch->offset);
			sub_bin->cputype = arch->cputype;
			sub_bin->cpusubtype = arch->cpusubtype;
			tmp = ft_lstnew_noalloc(sub_bin, sizeof(t_bin));
			ft_lstadd_sorted(list, tmp, cmp_bin);
			i++;
		}
		return 1;
	}
	return 0;
}

char *get_arch_name(cpu_type_t cpu)
{
	if (cpu == CPU_TYPE_X86_64)
		return "x86_64";
	if (cpu == CPU_TYPE_I386)
		return "i386";
	if (cpu == CPU_TYPE_MC680x0)
		return "mc680x0";
	if (cpu == CPU_TYPE_X86)
		return "x86";
	if (cpu == CPU_TYPE_MC98000)
		return "mc98000";
	if (cpu == CPU_TYPE_HPPA)
		return "hppa";
	if (cpu == CPU_TYPE_ARM)
		return "arm";
	if (cpu == CPU_TYPE_ARM64)
		return "arm64";
	if (cpu == CPU_TYPE_MC88000)
		return "mc88000";
	if (cpu == CPU_TYPE_SPARC)
		return "sparc";
	if (cpu == CPU_TYPE_I860)
		return "i860";
	if (cpu == CPU_TYPE_POWERPC)
		return "powerpc";
	if (cpu == CPU_TYPE_POWERPC64)
		return "powerpc64";
	return "unknown";
}

int check_cpu(t_list *list)
{
	t_bin *bin;

	if (!list)
		return 0;
	bin = list->content;
	if(bin->cputype == MACHINE_CPU)
		return 1;
	return 0;
}

int	is_fat(t_bin* bin)
{
	t_list *list;
	t_list *tmp;
	t_bin	*sub;
	t_bin	*origin;

	list = NULL;
	if (!save_fat(bin, &list))
		return 0;
//	ft_printf("#RIS FAT#N\n");
	if (check_cpu(list))
		magic_start((t_bin*)list->content);
	else
	{
		origin = get_origin(bin);
		tmp = list;
		while (tmp)
		{
			sub = (t_bin*)tmp->content;
			ft_printf("%s (for architecture %s):\n", origin->filename, get_arch_name(sub->cputype));
			magic_start(sub);
			tmp = tmp->next;
			if (tmp)
				ft_putendl("");
		}
	}
	ft_lstfree(&list);
	return 1;
}
