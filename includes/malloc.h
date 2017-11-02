/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 10:07:43 by mfrisby           #+#    #+#             */
/*   Updated: 2017/10/31 10:10:06 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>

# define TINYSIZE 	512
# define SMALLSIZE	1100

typedef struct			s_header {
	int					is_free;
	int					can_free;
	int					size;
	struct s_header		*next;
}						t_header;

typedef struct			s_zone
{
	int					tinypages;
	int					smallpages;
	void				*tinymem;
	void				*smallmem;
	t_header			*tinyhead;
	t_header			*smallhead;
	t_header			*largehead;
}						t_zone;

t_zone					g_zone;

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					*ft_mmap(int size);
void					*tiny_zone(int size, int zonesize);
void					*small_zone(int size, int zonesize);
void					show_alloc_mem();
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putstr(char const *s);
void					ft_putchar(char c);
void					aff_mem_addr(size_t dec);
void					*ft_memcpy(void *dst, const void *src, size_t n);

#endif
