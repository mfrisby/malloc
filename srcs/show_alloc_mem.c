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

static int		aff_alloc(int n)
{
	int			total;
	t_header	*h;

	total = 0;
	h = zones[n].head;
	while (h)
	{
		aff_mem_addr((size_t)((void*)h + 1));
		ft_putstr(" - ");
		aff_mem_addr((size_t)((void*)h + h->size));
		ft_putstr(" : ");
		ft_putnbr(h->size - HEADERSIZE);
		ft_putendl(" octets");
		total += h->size - HEADERSIZE;
		h = h->next;
	}
	return (total);
}

static void		aff_zone(int n)
{
	if (n == 0)
		ft_putstr("TINY : ");
	else if (n == 1)
		ft_putstr("SMALL : ");
	else if (n == 2)
		ft_putstr("LARGE : ");
	if (n < 2 && zones[n].mem)
		aff_mem_addr((size_t)((void*)zones[n].mem));
	else if (n == 2 && zones[n].head)
		aff_mem_addr((size_t)((void*)zones[n].head + 1));
	else
		ft_putstr("none");
	ft_putchar('\n');
}

void			show_alloc_mem(void)
{
	int			n;
	long long	total;

	n = 0;
	total = 0;
	while (n < 3)
	{
		aff_zone(n);
		total += aff_alloc(n);
		n++;
	}
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putendl(" octets");
}
