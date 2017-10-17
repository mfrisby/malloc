#include "../includes/malloc.h"
#include <string.h>
#include <stdio.h>
#include <errno.h>

static int     gettype(int size)
{
    int pagesize;

    pagesize = getpagesize();
    if (size <= pagesize)
        return (0);
    else if (size <= pagesize * 2)
        return (1);
    return (2);
}

static int     remove_header(t_header *h)
{
    t_header *tmp;
    int         n;
    int         size;

    size = h->size;
    n = gettype(size);
    tmp = zones[n].head;
    while (tmp && tmp->next)
    {
        if (tmp->next == h)
            break;
        tmp = tmp->next;
    }
    if (tmp)
    {
        tmp->next = h->next;
        if (h == zones[n].tail)
            zones[n].tail = tmp->next;
    }
    //TODO : free zone if empty ?
    return (size);
}

void			free(void *ptr)
{
    t_header *h;
    int size;

    if (!ptr)
        return;
    h = (t_header*)ptr - 1;
    if (h && h->size)
    {
        if (h->can_free == 1)
        {
            size = remove_header(h);
            munmap((void*)h, size);
        }
        else
            h->is_free = 1;
    }
}