# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmacquet <kmacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/02 13:02:47 by kmacquet          #+#    #+#              #
#    Updated: 2021/02/15 12:43:38 by kmacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Wextra -Werror -I./includes
SRCS = ft_printf.c
OBJS = $(SRCS:.c=.o)
ARRCS = ar -rcs
RM = rm -f

all: $(NAME)

.c.o:
		$(CC) $(FLAGS) -o $(<:.c=.o) -c $<

$(NAME):$(OBJS)
		$(ARRCS) $@ $(OBJS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all
