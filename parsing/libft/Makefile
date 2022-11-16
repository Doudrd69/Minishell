NAME = libft.a

FLAGS = -Wall -Wextra -Werror -g

CC = gcc

SRCS = srcs/

FILES = ft_atoi.c        	\
		ft_bzero.c       	\
		ft_calloc.c      	\
		ft_isalnum.c     	\
		ft_isalpha.c     	\
		ft_isascii.c     	\
		ft_isdigit.c     	\
		ft_isprint.c     	\
		ft_itoa.c        	\
		ft_memchr.c     	\
		ft_memcmp.c      	\
		ft_memcpy.c      	\
		ft_memmove.c     	\
		ft_memset.c      	\
		ft_putchar_fd.c  	\
		ft_putendl_fd.c  	\
		ft_putnbr_fd.c   	\
		ft_putstr_fd.c   	\
		ft_split.c       	\
		ft_strchr.c      	\
		ft_strdup.c      	\
		ft_strjoin.c     	\
		ft_strlcat.c     	\
		ft_strlcpy.c     	\
		ft_strlen.c      	\
		ft_strmapi.c     	\
		ft_strncmp.c     	\
		ft_strnstr.c     	\
		ft_strrchr.c     	\
		ft_strtrim.c     	\
		ft_substr.c      	\
		ft_tolower.c     	\
		ft_toupper.c     	\
		ft_striteri.c    	\
		ft_putnbr_basediu.c	\

BONUS_FILES =	ft_lstnew.c      	\
				ft_lstadd_front.c	\
				ft_lstsize.c     	\
				ft_lstlast.c     	\
				ft_lstadd_back.c 	\
				ft_lstdelone.c   	\
				ft_lstclear.c    	\
				ft_lstiter.c     	\
				ft_lstmap.c      	\

OBJ = ${FILES:.c=.o}

OBJ_B = ${BONUS_FILES:.c=.o}

all :		${NAME}

libft.a : 	${OBJ} ${OBJ_B}
			ar rc ${NAME} ${OBJ_B} ${OBJ}

%.o:		%.c libft.h
			${CC} $(FLAGS) -c $< -o $@

bonus :		${OBJ} ${OBJ_B}
			ar rc ${NAME} ${OBJ_B} ${OBJ}

clean :
			rm -f ${OBJ} ${OBJ_B}

fclean :	clean
			rm -f ${NAME}

re :		fclean all

.PHONY:		all clean fclean bonus .c.o re
