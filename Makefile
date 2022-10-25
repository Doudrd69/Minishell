CC = gcc
FLAGS = -Werror -Wextra -Wall -g

PRINTF_NAME = libftprintf.a
PRINTF_PATH = ./ft_printf/

LIBFT_NAME = libft.a
LIBFT_PATH = parsing/libft/

RL_LIB_DIR    := -L $(shell brew --prefix readline)/lib
RL_INC_DIR    := -I $(shell brew --prefix readline)/include

SRCS =	cmd_exec/cmd_main.c										\
		cmd_exec/cmd_srcs/main_utils_bonus.c					\
		cmd_exec/cmd_srcs/child_execution_bonus.c				\
		cmd_exec/cmd_srcs/split_path_bonus.c					\
		cmd_exec/cmd_srcs/main_pipe_creation.c					\
		cmd_exec/cmd_srcs/utils/first_command_utils.c			\
		cmd_exec/cmd_srcs/utils/last_command_utils.c			\
		cmd_exec/cmd_srcs/utils/single_quote_exec.c				\
		builtins/functions/builtin_functions.c					\
		builtins/functions/builtin_export_unset.c				\
		builtins/functions/utils/builtin_functions_utils.c		\
		builtins/functions/utils/mini_export_utils.c			\
		builtins/functions/utils/mini_unset_utils.c				\
		builtins/functions/utils/mini_echo_utils.c				\
		builtins/functions/utils/mini_export_existing_var.c		\
		builtins/functions/utils/mini_cd_utils.c				\
		builtins/functions/utils/mini_echo_check_var_utils.c	\
		builtins/functions/utils/mini_getenv_utils.c			\
		heredoc/heredoc.c										\
		heredoc/heredoc_utils.c									\
		heredoc/heredoc_execution.c								\
		heredoc/heredoc_functions.c								\
		heredoc/heredoc_env_var_handling_utils.c				\
		parsing/srcs/init_variable.c							\
		parsing/srcs/parsing.c									\
		parsing/srcs/exit.c										\
		parsing/srcs/path.c										\
		parsing/srcs/pipe.c										\
		parsing/srcs/pipe_bis.c									\
		parsing/srcs/redirections.c								\
		parsing/srcs/quote.c									\
		parsing/srcs/builtins.c									\
		parsing/srcs/dollars.c									\
		parsing/debug/print_all.c								\
		parsing/srcs/counter.c									\
		parsing/srcs/search_var.c								\
		parsing/srcs/search_var_bis.c							\
		parsing/srcs/dollars_include.c							\
		parsing/srcs/ft_dlstnew.c 								\
		parsing/srcs/ft_dlstadd_front.c							\
		parsing/srcs/ft_dlstadd_back.c							\
		parsing/srcs/space.c									\
		parsing/srcs/check_quote_dollars.c						\
		parsing/srcs/new_value_dollars.c						\
		parsing/srcs/new_value_export_dollars.c					\
		main_loop_utils.c										\
		no_env.c												\
		signal.c												\
		main.c											

INCS = 	cmd_exec/cmd_include/pipex_bonus.h						\
		parsing/parsing.h										\
		includes/minishell.h

OBJS = $(SRCS:.c=.o)

%.o : %.c $(PRINTF_PATH)$(PRINTF_NAME) $(LIBFT_PATH)$(LIBFT_NAME) $(INCS)
		$(CC) $(FLAGS) $(RL_INC_DIR) -c $< -o $@

NAME = minishell

all : ft_printf libft $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(RL_LIB_DIR) $(FLAGS) -L $(PRINTF_PATH) -L $(LIBFT_PATH) -lftprintf -lft -lreadline -o $(NAME) $(OBJS)

ft_printf :
	make -C $(PRINTF_PATH)

libft :
	make -C $(LIBFT_PATH)

$(PRINTF_PATH)$(PRINTF_NAME) : ft_printf

$(LIBFT_PATH)$(LIBFT_NAME) : libft

clean : 
	rm -f $(OBJS)
	make clean -C $(PRINTF_PATH)
	make clean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(PRINTF_PATH)
	make fclean -C $(LIBFT_PATH)

re : fclean all

.PHONY : all clean fclean re ft_printf libft