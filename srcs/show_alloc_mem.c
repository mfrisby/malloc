 #include "../includes/malloc.h"

static int aff_alloc(int n)
{
    int         total;
    t_header    *h;

    total = 0;
    h = zones[n].head;
    while (h)
    {
        
        aff_mem_addr((int)((void*)h + 1), 16);
        ft_putstr(" - ");
        aff_mem_addr((int)((void*)h + h->size), 16);
        ft_putstr(" : ");
        ft_putnbr(h->size);
        ft_putendl("octets");
        total += h->size;
        h = h->next;
    }
    return (total);
}

static void aff_zone(int n)
{
    if (n == 0)
        ft_putstr("TINY : ");
    else if (n == 1)
        ft_putstr("SMALL : ");
    else if (n == 2)
        ft_putstr("LARGE : ");
    if (n < 2 && zones[n].mem)
        aff_mem_addr((int)zones[n].mem, 16);
    else if (n == 2 && zones[n].head)
        aff_mem_addr((int)((void*)zones[n].head + 1), 16);
    ft_putchar('\n');
}

void        show_alloc_mem()
{
    int n;
    int total;

    n = 0;
    total = 0;
    while (n < 3)
    {
        aff_zone(n);
        total += aff_alloc(n);
        n++;
    }
    ft_putstr("Total : ");
    ft_putnbr(total);
    ft_putendl("octets");
}