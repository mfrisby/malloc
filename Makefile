ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME =	libft_malloc_$(HOSTTYPE).so

LN = 	libft_malloc.so

SRC =	./srcs/malloc.c ./srcs/free.c ./srcs/realloc.c\
		./srcs/show_alloc_mem.c ./srcs/ft_mmap.c ./srcs/add_header.c\
		./srcs/ft_putstr.c ./srcs/ft_putendl.c ./srcs/ft_putnbr.c ./srcs/ft_putchar.c \
		./srcs/ft_memcpy.c srcs/aff_mem_addr.c\
		
		#srcs/ft_utoa_base.c\

FLAGS =	-Wall -Wextra -Werror -O2 -fPIC -g

all:	$(NAME)

%.o :	%.c
		gcc -c -o $@ $^

$(NAME): $(SRC)
	@gcc $(FLAGS) -I./includes -o $@ -c $<
	gcc $(FLAGS) -shared -o $@ $^
	ln -s $@ $(LN)

clean:
	/bin/rm -f $(SRC2) $(NAME) libft_malloc.so

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re