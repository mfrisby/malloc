#include "../includes/malloc.h"

static int     gettype(int size)
{
    if (size <= TOTALTINYSIZE)
        return (0);
    else if (size <= TOTALSMALLSIZE)
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
            if (munmap((void*)h, size) == -1)
                ft_putstr("\033[34mFAILED\033[0m");
            else
                ft_putstr("\033[31mSUCCESS\033[0m");
        }
        else
        {
            ft_putstr("-not-");
            h->is_free = 1;
        }
    }
    else
    {
        ft_putstr("\033[31mh\033[0m");
        ptr = NULL;
    }
}