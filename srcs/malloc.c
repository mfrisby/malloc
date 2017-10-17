#include "../includes/malloc.h"
#include <stdio.h>

static void *new_mem(int size, int n)
{
    t_header *h;
    void *ptr;
    
    ft_putstr("\033[35m mem \033[00m");
    if (!zones[n].head)
    {
        zones[n].pages = 0;
        zones[n].head = NULL;
        zones[n].tail = NULL;
    }
    ptr = ft_mmap(size + HEADERSIZE);
    h = ptr;
    if (!h)
        return (NULL);
    h = add_header(h, size + HEADERSIZE, 1, 2);
    return ((void*)(h + 1));
}

static void *get_free_space(int size, int n)
{
    t_header *h;
    int i;

    ft_putstr("\033[31m getfreespace \033[00m");
    i = 0;
    h = zones[n].head;
    while (h)
    {
        if (h->is_free == 1)
            return ((void*)(h + 1));
        h = h->next;
    }
    return (new_mem(size, n));
}

// static void *small_zone(int size)
// {
//     t_header *h;
//     int i;
    
//     i = 0;
//     h = NULL;
//     if (!zones[1].mem)
//     {
//         zones[1].pages = 0;
//         zones[1].mem = ft_mmap(SMALLZONE);
//         zones[1].head = NULL;
//         zones[1].tail = NULL;
//     }
//     while (i <= zones[1].pages)
//         i++;
//     i *= TOTALSMALLSIZE;
//     if (i >= (int)SMALLZONE)
//         return (get_free_space(size, 1));
//     //ft_putstr("\033[33ms\033[0m");
//     h = zones[1].mem + zones[1].pages * TOTALTINYSIZE;
//     zones[1].pages++;
//     if (!h)
//         return (NULL);
//     h = add_header(h, size + HEADERSIZE, 0, 1);
//     return (void*)(h + 1);
// }

// static void *tiny_zone(int size)
// {
//     t_header *h;
//     int i;

//     i = 0;
//     h = NULL;
//     if (!zones[0].mem)
//     {
//         zones[0].pages = 0;
//         zones[0].mem = ft_mmap(TINYZONE);
//         zones[0].head = NULL;
//         zones[0].tail = NULL;
//     }
//     while (i <= zones[0].pages)
//         i++;
//     i *= TOTALTINYSIZE;
//     if (i >= (int)TINYZONE)
//         return (get_free_space(size, 0));
//     //ft_putstr("\033[30mt\033[0m");
//     h = zones[0].mem + zones[0].pages * TOTALTINYSIZE;
//     if (!h)
//         return (NULL);
//     h = add_header(h, size + HEADERSIZE, 0, 0);
//     zones[0].pages++;
//     return (void*)(h + 1);
// }

static void *mem_zone(int size, int n, int pagesize)
{
    t_header *h;
    int i;
    int zone;

    h = NULL;
    i = 0;
    zone = pagesize * NBALLOC;
    if (!zones[n].mem)
    {
        zones[n].pages = 0;
        ft_putstr("zone: ");
        ft_putnbr(n);
        ft_putchar('\n');
        zones[n].mem = ft_mmap(zone);
        zones[n].head = NULL;
        zones[n].tail = NULL;
    }
    if (NBALLOC <= zones[n].pages)
        get_free_space(size, n);
    h = zones[n].mem + zones[n].pages * (pagesize);    
    if (!h)
        return (NULL);
    h = add_header(h, pagesize, 0, 0);
    zones[n].pages++;
    ft_putstr("\033[42m zone \033[00m");
    return (void*)(h + 1);
}

void		*malloc(size_t size)
{
    int pagesize;
    void *ptr;
    int i;

    i = 1;
    pagesize = getpagesize();
    if (size <= 0)
        return (NULL);
    else if ((int)size + (int)HEADERSIZE <= pagesize / 4)
        ptr = mem_zone(size, 0, pagesize / 4);
    else if ((int)size + (int)HEADERSIZE <= pagesize / 2)
        ptr = mem_zone(size, 1, pagesize / 2);
    else
    {
        if ((int)size + (int)HEADERSIZE <= pagesize)
            ptr = new_mem(pagesize, 2);
        else
        {
            while ((int)size > pagesize * i)
                i++;
            ptr = new_mem(pagesize * i, 2);
        }
    }
    // else if (size <= TINYMAXSIZE)
    //     ptr = tiny_zone(size);
    // else if (size <= SMALLMAXSIZE)
    //     ptr = small_zone(size);
    return (ptr);
}