/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_mem_addr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:50:11 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/18 15:50:30 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void		aff_mem_addr(size_t dec)
{
	size_t	i;

	if (dec)
	{
		i = dec / 16;
		aff_mem_addr(i);
		if (dec % 16 < 10)
			ft_putchar('0' + dec % 16);
		else
			ft_putchar('a' + (dec % 16) - 10);
	}
	else
		ft_putstr("0x");
	return ;
}
