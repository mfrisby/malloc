#include "../includes/malloc.h"
t_header *add_header(t_header *h, int size, int can_free)
{
    h->can_free = can_free;
    h->size = size;
    h->is_free = 0;
    h->next = NULL;
    if (!zones.head)
        zones.head = h;
    if (zones.tail)
        zones.tail->next = h;
    zones.tail = h;
    return (h);
}