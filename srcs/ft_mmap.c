
#include "../includes/malloc.h"

void        *ft_mmap(int size)
{
    void    *ptr;

    ptr = NULL;
	if ((ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == ((void *)-1))
	    return (NULL);
    return (ptr);
}