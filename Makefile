# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achu <achu@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/14 12:53:14 by achu              #+#    #+#              #
#    Updated: 2025/02/21 17:19:25 by achu             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
INCLUDE = includes
LIBFT =  lib/libft
HEADERS = $(LIBFT)/libft.h src/pipex.h

SRC =	src/main.c \
		src/checker.c \
		src/parser.c \
		src/execute.c \
		src/cleaner.c \
		src/utils.c \
		src/heredoc.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT)/libft.a -o $(NAME)

%.o: %.c
	$(CC) $(INCLUDES) -I $(LIBFT) -c $< -o $@

$(OBJS): $(HEADERS)

clean:
	$(MAKE) clean -C $(LIBFT)
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re