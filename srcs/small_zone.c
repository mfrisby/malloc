/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_zone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 13:30:58 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/24 13:52:56 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		add_header(t_header *h)
{
	t_header *tmp;

	tmp = g_zone.smallhead;
	if (!tmp)
	{
		g_zone.smallhead = h;
		return ;
	}
	while (tmp && tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = h;
}

static void		*get_free_space(int size)
{
	t_header	*tmp;

	tmp = g_zone.smallhead;
	while (tmp)
	{
		if (tmp->is_free == 1)
		{
			tmp->size = size + sizeof(t_header);
			tmp->is_free = 0;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void		*add_in_zone(int size)
{
	t_header	*h;

	h = g_zone.smallmem + (g_zone.smallpages * SMALLSIZE) + 1;
	if (!h)
		return (NULL);
	h->can_free = 0;
	h->is_free = 0;
	g_zone.smallpages++;
	h->size = size + sizeof(t_header);
	add_header(h);
	return (h);
}

static void		*add_out_zone(int size)
{
	t_header	*h;

	h = ft_mmap(size + sizeof(t_header));
	if (!h)
		return (NULL);
	h->can_free = 1;
	h->is_free = 0;
	h->size = size + sizeof(t_header);
	h->next = NULL;
	add_header(h);
	return (h);
}

void			*small_zone(int size, int zonesize)
{
	t_header	*h;

	h = NULL;
	if (!g_zone.smallmem)
	{
		g_zone.smallmem = ft_mmap(zonesize);
		h = g_zone.smallmem;
		h->can_free = 0;
		h->is_free = 0;
		h->size = size + sizeof(t_header);
		h->next = NULL;
		g_zone.smallhead = h;
		g_zone.smallpages = 1;
		return (h);
	}
	if ((h = get_free_space(size)))
		return (h);
	if (zonesize <= (g_zone.smallpages) * SMALLSIZE)
		h = add_out_zone(size);
	else
		h = add_in_zone(size);
	return (h);
}
