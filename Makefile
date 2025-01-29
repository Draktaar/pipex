# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achu <achu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 12:53:14 by achu              #+#    #+#              #
#    Updated: 2025/01/28 23:49:50 by achu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
INCLUDE = includes
LIBFT =  lib/libft
PRINTF =  lib/printf
HEADERS = $(LIBFT)/libft.h $(PRINTF)/ft_printf.h src/pipex.h

SRC =	src/main.c \
		src/parser.c \
		src/checker.c \
		src/execute.c \
		src/cleaner.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(MAKE) -C $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) -g3 $(LIBFT)/libft.a $(PRINTF)/printf.a -o $(NAME)

%.o: %.c
	$(CC) $(INCLUDES) -g3 -I $(LIBFT) $(PRINTF) -c $< -o $@

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