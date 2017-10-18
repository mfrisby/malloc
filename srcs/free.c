/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:50:37 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/18 15:51:48 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static int		gettype(int size)
{
	int			pagesize;

	pagesize = getpagesize();
	if (size <= pagesize)
		return (0);
	else if (size <= pagesize * 2)
		return (1);
	return (2);
}

static int		remove_header(t_header *h)
{
	t_header	*tmp;
	int			n;
	int			size;

	size = h->size;
	n = gettype(size);
	tmp = zones[n].head;
	while (tmp && tmp->next)
	{
		if (tmp->next == h)
			break ;
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
	t_header	*h;
	int			size;

	if (!ptr)
		return ;
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
