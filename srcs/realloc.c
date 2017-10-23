/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:56:50 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/18 16:01:45 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

// static void		*valid_ptr(t_header *h, size_t size, size_t oldsize, void *ptr)
// {
// 	void		*newptr;

// 	newptr = NULL;
// 	if (h && h->can_free == 0 && h->is_free == 0)
// 		return (NULL);
// 	if (h && h->is_free == 0 && h->size > 0)
// 	{
// 		oldsize = h->size;
// 		newptr = malloc(size);
// 		if (oldsize <= size)
// 			newptr = ft_memcpy(newptr, ptr, oldsize);
// 		else
// 			newptr = ft_memcpy(newptr, ptr, size);
// 		free(ptr);
// 	}
// 	else
// 		return (NULL);
// 	return (newptr);
// }

void			*realloc(void *ptr, size_t size)
{
	t_header	*h;
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
	h = (void*)ptr - sizeof(t_header);
	return (malloc(size));//TEST
	//return (valid_ptr(h, size, oldsize, ptr));
}
