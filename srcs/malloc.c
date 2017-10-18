/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:54:46 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/18 15:56:46 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void		*new_mem(int size, int n)
{
	t_header	*h;
	void		*ptr;

	if (!zones[n].head)
	{
		zones[n].pages = 0;
		zones[n].head = NULL;
		zones[n].tail = NULL;
	}
	ptr = ft_mmap(size + HEADERSIZE);
	h = ptr;
	if (!h)
		return (NULL);
	h = add_header(h, size + HEADERSIZE, 1, n);
	return ((void*)(h + 1));
}

static void		*get_free_space(int size, int n)
{
	t_header	*h;

	h = zones[n].head;
	while (h)
	{
		if (h->is_free == 1)
		{
			h->is_free = 0;
			add_header(h, size + HEADERSIZE, 0, n);
			return ((void*)(h + 1));
		}
		h = h->next;
	}
	return (new_mem(size, n));
}

static void		*mem_zone(int size, int n, int pagesize)
{
	t_header	*h;
	int			i;
	int			zone;

	h = NULL;
	i = 0;
	zone = pagesize * NBALLOC;
	if (!zones[n].mem)
	{
		zones[n].pages = 0;
		zones[n].mem = ft_mmap(zone);
		zones[n].head = NULL;
		zones[n].tail = NULL;
	}
	if (NBALLOC <= zones[n].pages)
		return (get_free_space(size, n));
	h = zones[n].mem + zones[n].pages * (pagesize);
	if (!h)
		return (NULL);
	h = add_header(h, size + HEADERSIZE, 0, n);
	zones[n].pages++;
	return (void*)(h + 1);
}

void			*malloc(size_t size)
{
	void		*ptr;
	int			i;

	i = 1;
	if (size <= 0)
		return (NULL);
	else if ((int)size + (int)HEADERSIZE <= TINYSIZE)
		ptr = mem_zone(size, 0, TINYSIZE);
	else if ((int)size + (int)HEADERSIZE <= SMALLSIZE)
		ptr = mem_zone(size, 1, SMALLSIZE);
	else
		ptr = new_mem(size, 2);
	return (ptr);
}
