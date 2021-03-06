/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_zone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/24 13:29:30 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/24 13:53:32 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		add_header(t_header *h)
{
	t_header *tmp;

	tmp = g_zone.tinyhead;
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

	tmp = g_zone.tinyhead;
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

static void		*add_in_zone(t_header *h, int size)
{
	h = g_zone.tinymem + (g_zone.tinypages * TINYSIZE) + 1;
	h->can_free = 0;
	h->is_free = 0;
	g_zone.tinypages++;
	h->size = size + sizeof(t_header);
	add_header(h);
	return (h);
}

static void		*add_out_zone(t_header *h, int size)
{
	h = ft_mmap(size + sizeof(t_header));
	h->can_free = 1;
	h->is_free = 0;
	h->size = size + sizeof(t_header);
	h->next = NULL;
	add_header(h);
	return (h);
}

void			*tiny_zone(int size, int zonesize)
{
	t_header *h;

	h = NULL;
	if (!g_zone.tinymem)
	{
		g_zone.tinymem = ft_mmap(zonesize);
		h = g_zone.tinymem;
		h->can_free = 0;
		h->is_free = 0;
		h->size = size + sizeof(t_header);
		h->next = NULL;
		g_zone.tinyhead = h;
		g_zone.tinypages = 1;
		return (h);
	}
	h = get_free_space(size);
	if (h)
		return (h);
	if (zonesize <= (g_zone.tinypages + 1) * SMALLSIZE)
		h = add_out_zone(h, size);
	else
		h = add_in_zone(h, size);
	return ((void*)h);
}
