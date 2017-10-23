/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:02:01 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/18 16:02:44 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static int		aff_alloc(t_header *h)
{
	int			total;

	total = 0;
	while (h)
	{
		aff_mem_addr((size_t)((void*)h + 1));
		ft_putstr(" - ");
		aff_mem_addr((size_t)((void*)h + h->size));
		ft_putstr(" : ");
		ft_putnbr(h->size - sizeof(t_header));
		ft_putendl(" octets");
		total += h->size - sizeof(t_header);
		h = h->next;
	}
	return (total);
}

static void		aff_zone(t_header *head, int n)
{
	if (n == 0)
		ft_putstr("TINY : ");
	else if (n == 1)
		ft_putstr("SMALL : ");
	else if (n == 2)
		ft_putstr("LARGE : ");
	if (n == 0 && g_zone.tinymem)
		aff_mem_addr((size_t)((void*)g_zone.tinymem));
	if (n == 1 && g_zone.smallmem)
		aff_mem_addr((size_t)((void*)g_zone.smallmem));
	else if (n == 2 && head)
		aff_mem_addr((size_t)((void*)head + 1));
	else
		ft_putstr("none");
	ft_putchar('\n');
}

void			show_alloc_mem(void)
{
	t_header	*h;
	int			n;
	long long	total;

	n = 0;
	total = 0;
	while (n < 3)
	{
		if (n == 0)
			h = g_zone.tinyhead;
		else if (n == 1)
			h = g_zone.smallhead;
		else
			h = g_zone.largehead;
		aff_zone(h, n);
		total += aff_alloc(h);
		n++;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
}
