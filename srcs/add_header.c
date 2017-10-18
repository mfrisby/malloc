/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:14:49 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/18 15:15:04 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_header	*add_header(t_header *h, int size, int can_free, int n)
{
	h->can_free = can_free;
	h->size = size;
	h->is_free = 0;
	h->next = NULL;
	if (!zones[n].head)
		zones[n].head = h;
	if (zones[n].tail)
		zones[n].tail->next = h;
	zones[n].tail = h;
	return (h);
}
