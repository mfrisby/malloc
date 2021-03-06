/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 13:07:01 by mfrisby           #+#    #+#             */
/*   Updated: 2017/07/17 10:47:24 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../includes/malloc.h"

void	ft_putstr(char const *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i])
		i++;
	write(1, s, i);
}
