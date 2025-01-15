# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achu <achu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 12:53:14 by achu              #+#    #+#              #
#    Updated: 2025/01/14 19:42:06 by achu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
INCLUDE = includes
LIBFT =  lib/libft
PRINTF =  lib/printf
HEADERS = $(LIBFT)/libft.h $(PRINTF)/ft_printf.h pipex.h

SRC =	main.c \
		parser.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(PRINTF)
	$(CC) $(OBJS) $(LIBFT)/libft.a $(PRINTF)/printf.a -o $(NAME)

%.o: %.c
	$(CC) $(INCLUDES) -I $(LIBFT) $(PRINTF) -c $< -o $@

$(OBJS): $(HEADERS)

clean:
	$(MAKE) clean -C $(LIBFT)
	$(MAKE) clean -C $(PRINTF)
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	$(MAKE) fclean -C $(PRINTF)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re