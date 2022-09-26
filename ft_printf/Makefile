# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 09:37:34 by ebrodeur          #+#    #+#              #
#    Updated: 2021/11/30 12:56:58 by ebrodeur         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Werror -Wextra -Wall -g

SRCS =	srcs/ft_printf.c \
		srcs/ft_sort_params.c \
		srcs/ft_sort_params_utils.c \


OBJECTS = ${SRCS:.c=.o}

%.o : %.c includes/ft_printf.h includes/ft_sort_params.h
		gcc ${FLAGS} -c $< -o $@

$(NAME) : ${OBJECTS}
	ar -rc ${NAME} $?

all : ${NAME} 

clean : 
	rm -f ${OBJECTS}

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY : all clean fclean re