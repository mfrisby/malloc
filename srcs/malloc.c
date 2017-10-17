#include "../includes/malloc.h"

static void *new_mem(int size, int n)
{
    t_header *h;
    void *ptr;
    
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

static void *small_zone(int size)
{
    t_header *h;
    int i;
    
    i = 0;
    h = NULL;
    if (!zones[1].mem)
    {
        zones[1].pages = 0;
        zones[1].mem = ft_mmap(SMALLZONE);
        zones[1].head = NULL;
        zones[1].tail = NULL;
    }
    while (i <= zones[1].pages)
        i++;
    i *= TOTALSMALLSIZE;
    if (i >= SMALLZONE)
    {
        ft_putstr("\033[45ms\033[0m");
        return (get_free_space(size, 1));
        //return (new_mem(size, 1));
    }
    ft_putstr("\033[33ms\033[0m");
    h = zones[1].mem + zones[1].pages * TOTALTINYSIZE;
    zones[1].pages++;
    if (!h)
        return (NULL);
    h = add_header(h, size + HEADERSIZE, 0, 1);
    return (void*)(h + 1);
}

static void *tiny_zone(int size)
{
    t_header *h;
    int i;

    i = 0;
    h = NULL;
    if (!zones[0].mem)
    {
        zones[0].pages = 0;
        zones[0].mem = ft_mmap(TINYZONE);
        zones[0].head = NULL;
        zones[0].tail = NULL;
    }
    while (i <= zones[0].pages)
        i++;
    i *= TOTALTINYSIZE;
    if (i >= TINYZONE)
    {
        ft_putstr("\033[45mt\033[0m");
        return (new_mem(size, 0));
    }
    ft_putstr("\033[30mt\033[0m");
    h = zones[0].mem + zones[0].pages * TOTALTINYSIZE;
    if (!h)
        return (NULL);
    h = add_header(h, size + HEADERSIZE, 0, 0);
    zones[0].pages++;
    return (void*)(h + 1);
}

void		*malloc(size_t size)
{
    void *ptr;

    if (size <= 0)
        return (NULL);
    else if (size <= TINYMAXSIZE)
        ptr = tiny_zone(size);
    else if (size <= SMALLMAXSIZE)
        ptr = small_zone(size);
    else
        ptr = new_mem(size, 2);
    return (ptr);
}