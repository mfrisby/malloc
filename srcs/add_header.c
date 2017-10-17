#include "../includes/malloc.h"
t_header *add_header(t_header *h, int size, int can_free, int n)
{
    h->can_free = can_free;
    h->size = size;
    h->is_free = 0;
    h->next = NULL;
    if (!zones[n].head)
        zones[n].head = h;
    if (zones[n].tail)
        zones[n].tail->next = h;
    zones[n].tail = h;
    return (h);
}