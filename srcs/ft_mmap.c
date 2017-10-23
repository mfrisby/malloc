/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 15:51:59 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/18 15:53:55 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"
#include <sys/mman.h>

void		*ft_mmap(int size)
{
	void	*ptr;

	ptr = NULL;
	if ((ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANON |
					MAP_PRIVATE, -1, 0)) == ((void *)-1))
		return (NULL);
	return (ptr);
}
