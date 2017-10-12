#include "../includes/malloc.h"

static int     remove_header(t_header *h)
{
    t_header *tmp;
    int         size;

    size = h->size;
    tmp = zones.head;
    while (tmp && tmp->next)
    {
        if (tmp->next == h)
            break;
        tmp = tmp->next;
    }
    if (tmp)
    {
        tmp->next = h->next;
        if (h == zones.tail)
            zones.tail = tmp->next;
    }
    return (size);
}

void			free(void *ptr)
{
    t_header *h;
    int size;

    if (ptr == NULL)
        return;
    h = (t_header*)ptr - 1;
    if (h && h->size)
    {
        if (h->can_free == 1)
        {
            size = remove_header(h);
            if (munmap((void*)h, size) == -1)
                ft_putendl("munmap failed");
            else
                ft_putendl("SUCCESS FREE");
        }
        else
            h->is_free = 1;
    }
    ptr = NULL;
}