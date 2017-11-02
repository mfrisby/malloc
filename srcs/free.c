/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 13:33:15 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/24 13:49:14 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <sys/mman.h>

static t_header	*getheadzone(int size)
{
	if (size <= TINYSIZE)
		return (g_zone.tinyhead);
	else if (size <= SMALLSIZE)
		return (g_zone.smallhead);
	else if (size > SMALLSIZE)
		return (g_zone.largehead);
	return (NULL);
}

static int		remove_header(t_header *h)
{
	t_header	*tmp;
	int			size;

	tmp = getheadzone(h->size);
	size = h->size;
	while (tmp && tmp->next)
	{
		if (tmp->next == h)
		{
			tmp->next = h->next;
			return (size);
		}
		tmp = tmp->next;
	}
	return (-1);
}

static int		is_ok(t_header *h)
{
	t_header	*tmp;

	tmp = g_zone.tinyhead;
	while (tmp)
	{
		if (h == tmp)
			return (1);
		tmp = tmp->next;
	}
	tmp = g_zone.smallhead;
	while (tmp)
	{
		if (h == tmp)
			return (1);
		tmp = tmp->next;
	}
	tmp = g_zone.largehead;
	while (tmp)
	{
		if (h == tmp)
			return (1);
		tmp = tmp->next;
	}
	return (-1);
}

void			free(void *ptr)
{
	int			size;
	t_header	*h;

	size = 0;
	if (!ptr)
		return ;
	h = ptr - sizeof(t_header);
	if (h && is_ok(h) == 1)
	{
		if (h->can_free == 1)
		{
			size = remove_header(h);
			if (size > 0)
				munmap((void*)h, h->size);
		}
		else
			h->is_free = 1;
	}
}
