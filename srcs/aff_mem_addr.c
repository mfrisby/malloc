#include "../includes/malloc.h"

static int		ft_unblen_base(unsigned long long n, int base)
{
    int			len;
    long double	pow;
 
    pow = 1;
    len = 0;
    while (n >= (pow *= base))
        len++;
    return (len + 1);
}

static void		print_addr(int len, int nb, int base)
{
	char    s[len];
	
	if (nb == 0)
	{
		s[0] = '0';
		s[1] = 0;
		ft_putstr(s);
	}
	while (nb)
	{
		s[--len] = nb % base > 9 ? nb % base - 10 + 'a' : nb % base + '0';
		nb /= base;
	}
	ft_putstr(s);
}

void 			aff_mem_addr(int nb, int base)
{
	int len;

	ft_putstr("0x");
	len = ft_unblen_base(nb, base);
	print_addr(len, nb, base);
}