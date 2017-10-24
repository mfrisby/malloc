/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 13:31:55 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/24 13:48:56 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/malloc.h"

static void		basic_header(t_header *h, int can_free, int size)
{
	t_header	*tmp;

	tmp = g_zone.largehead;
	h->can_free = can_free;
	h->is_free = 0;
	h->size = size;
	if (!tmp)
	{
		g_zone.largehead = h;
		return ;
	}
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = h;
}

void			*malloc(size_t size)
{
	void		*ptr;

	ptr = NULL;
	if (size <= 0)
		return (NULL);
	if (size + sizeof(t_header) < TINYSIZE)
		ptr = tiny_zone(size);
	else if (size + sizeof(t_header) <= SMALLSIZE)
		ptr = small_zone(size);
	else
	{
		ptr = ft_mmap(size + sizeof(t_header));
		basic_header(ptr, 1, size + sizeof(t_header));
	}
	if (ptr)
		ptr = ptr + sizeof(t_header);
	return (ptr);
}
