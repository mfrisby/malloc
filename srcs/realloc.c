
#include "../includes/malloc.h"

void		*realloc(void *ptr, size_t size)
{
	t_header	*h;
	void		*newptr;
	size_t		oldsize;

	oldsize = 0;
	h = NULL;
    if (size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(size));
	h = (t_header*)ptr - 1;
	if (h && h->can_free == 0 && h->is_free == 0)
		return (NULL);
	if (h && h->is_free == 0 && h->size > 0)
	{
		oldsize = h->size;
		newptr = malloc(size);
		if (oldsize <= size)
			newptr = ft_memcpy(newptr, ptr, oldsize);
		else
			newptr = ft_memcpy(newptr, ptr, size);
		free(ptr);
	}
	else
		return (NULL);
    return (newptr);
}