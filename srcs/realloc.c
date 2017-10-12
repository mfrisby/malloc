
#include "../includes/malloc.h"

// static void	*ft_memcpy(void *dst, const void *src, size_t n)
// {
// 	char	*str1;
// 	char	*str2;
// 	size_t	i;

// 	i = 0;
// 	str1 = (char*)dst;
// 	str2 = (char*)src;
// 	while (i < n)
// 	{
// 		str1[i] = str2[i];
// 		i++;
// 	}
// 	return (dst);
// }

void		*realloc(void *ptr, size_t size)
{
    if (size <= 0)
        return (NULL);
    free(ptr);
    return (malloc(size));
	// size_t newsize;
	// void	*newptr;

	// newptr = NULL;
	// newsize = size > sizeof(ptr) ? sizeof(ptr) : size;
	// if (size <= 0)
	// 	free(ptr);
	// if ((int)size > 0)
	// 	newptr = malloc(size);
	// if (newptr && ptr)
	// 	newptr = ft_memcpy(newptr, ptr, newsize);
	// if (ptr)
	// 	free(ptr);
	// return (newptr);
}