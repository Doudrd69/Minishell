NAME =		minishell

CFLAGS =	-Wall -Wextra -Werror -I .

SFLAGS =	-fsanitize=address -g

CC =		gcc

LIBSDIR =	libft/

OBJS_DIR = .objs

OBJ =	$(addprefix $(OBJS_DIR)/, $(FILES:.c=.o))

FILES = srcs/main.c								\
		srcs/init_variable.c					\
		srcs/parsing.c							\
		srcs/exit.c								\
		srcs/path.c								\
		srcs/pipe.c								\
		srcs/pipe_bis.c							\
		srcs/redirections.c						\
		srcs/quote.c							\
		srcs/builtins.c							\
		srcs/dollars.c							\
		debug/print_all.c						\
		srcs/counter.c							\
		srcs/search_var.c						\
		srcs/search_var_bis.c					\
		srcs/dollars_include.c					\
		srcs/ft_dlstnew.c 						\
		srcs/ft_dlstadd_front.c					\
		srcs/ft_dlstadd_back.c					\
		srcs/space.c							\
		srcs/check_quote_dollars.c				\

all: libs $(NAME)

libs:
	$(MAKE) -C $(LIBSDIR)

$(NAME): $(OBJ) $(LIBSDIR)libft.a
	$(CC) $(SFLAGS) $(OBJ) -lreadline $(LIBSDIR)libft.a -o $(NAME)
	
$(OBJS_DIR)/%.o:		%.c minishell.h ${LIBSDIR}libft.h ${LIBSDIR}libft.a Makefile
				mkdir -p $(dir $@)
				${CC} ${CFLAGS} -I$(LIBSDIR) -c $< -o $@

clean :
				${MAKE} clean -C ${LIBSDIR}
				rm -f ${OBJ} ${OBJ_B} $(OBJS_DIR)/*.o 

fclean :
				${MAKE} fclean -C ${LIBSDIR}
				rm -f ${OBJ} ${OBJ_B} $(OBJS_DIR)/*.o
				rm -f ${NAME}
				rm -rf $(OBJS_DIR)

re :			fclean all

.PHONY:			all clean fclean bonus libs re objs