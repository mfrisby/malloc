#include "../includes/malloc.h"

static void *large_ptr(int size)
{
    t_header *h;
    void *ptr;

    ptr = ft_mmap(size + HEADERSIZE);
    h = ptr;
    if (!h)
    {
        ft_putendl("problem");
        return (NULL);
    }
    h = add_header(h, size + HEADERSIZE, 1);
    return ((void*)(h + 1));
}

// static void *get_free_space(size)
// {
//     // t_header *h;
//     // int i;

//     // i = 0;
//     // if (size <= (int)(TINYMAXSIZE))
//     // {
//     //     while (i < TINYZONE)
//     //     {
//     //         h = (t_header*)zones.ptiny + i;
//     //         if (h)
//     //         {
//     //             if (h->is_free == 1)
//     //             {
//     //                 h->is_free = 0;
//     //                 return (zones.ptiny + i);
//     //             }
//     //         }
//     //         i += TINYMAXSIZE;
//     //     }
//     // }
//     // else if (size <= (int)(SMALLMAXSIZE))
//     // {
//     //     while (i < TINYZONE)
//     //     {
//     //         h = (t_header*)zones.psmall + i;
//     //         if (h)
//     //         {
//     //             if (h->is_free == 1)
//     //             {
//     //                 h->is_free = 0;
//     //                 return (zones.psmall + i);
//     //             }
//     //         }
//     //         i += SMALLMAXSIZE;
//     //     }
//     // }
//     // ft_putendl("no place");
//     return (large_ptr(size));
// }

static void *small_zone(int size)
{
    t_header *h;
    int i;
    
    i = 0;
    h = NULL;
    if (!zones.psmall)
    {
        zones.small_page = 0;
        zones.psmall = ft_mmap(SMALLZONE);
    }
    while (i <= zones.small_page)
        i++;
    i *= SMALLMAXSIZE;
    if (i >= SMALLZONE)
        return (NULL);//(large_ptr(size));
    zones.small_page++;
    h = zones.psmall + i;
    if (!h)
    {
        ft_putendl("problem");
        return (NULL);
    }
    h = add_header(h, size, 0);
    return (void*)(h + 1);
}

static void *tiny_zone(int size)
{
    t_header *h;
    int i;

    i = 0;
    h = NULL;
    if (!zones.ptiny)
    {
        zones.tiny_page = 0;
        zones.ptiny = ft_mmap(TINYZONE);
    }
    while (i <= zones.tiny_page)
        i++;
    i *= TINYMAXSIZE;
    if (i >= TINYZONE)
        return (NULL);//(large_ptr(size));
    zones.tiny_page++;
    h = zones.ptiny + zones.tiny_page * TOTALTINYZONE;
    if (!h)
    {
        ft_putendl("problem");
        return (NULL);
    }
    h = add_header(h, size, 0);
    return (void*)(h + 1);
}

void		*malloc(size_t size)
{
    void *ptr;

    if (size <= 0)
        return (NULL);
    else if (size <= TINYMAXSIZE)
    {
        ptr = tiny_zone(size);
        ft_putstr("e");
    }
    else if (size <= SMALLMAXSIZE)
    {
        ptr = small_zone(size);
        ft_putstr("e");
    }
    else
    {
        ft_putstr("l");
        ptr = large_ptr(size);
    }
    return (ptr);
}