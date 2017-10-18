/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftmalloc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfrisby <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 10:58:59 by mfrisby           #+#    #+#             */
/*   Updated: 2017/07/17 11:47:55 by mfrisby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>     
# include <stdlib.h>
# include <sys/time.h> 
# include <sys/resource.h>
# include <sys/mman.h>

#define HEADERSIZE      sizeof(t_header)

#define NBALLOC         150

typedef struct          s_header {
	unsigned            is_free;
	unsigned            can_free;
    int                 size;
    struct s_header     *next;
}                       t_header;

typedef struct             s_zones
{
    int                    pages;
    void                   *mem;
    t_header               *head;
    t_header               *tail;
}                          t_zones;

t_zones                     zones[3];

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void        *ft_mmap(int size);
void        show_alloc_mem();
void	    ft_putendl(char const *s);
void	    ft_putnbr(int n);
void	    ft_putstr(char const *s);
void	    ft_putchar(char c);
void        aff_mem_addr(int nb, int base);
void        *ft_memcpy(void *dst, const void *src, size_t n);
t_header    *add_header(t_header *h, int size, int can_free, int n);
//char		*ft_utoa_base(unsigned long long nb, int base);


#endif
