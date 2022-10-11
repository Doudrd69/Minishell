CC = gcc
FLAGS = -Werror -Wextra -Wall -fsanitize=address -g

PRINTF_NAME = libftprintf.a
PRINTF_PATH = ./ft_printf/

RL_LIB_DIR    := -L $(shell brew --prefix readline)/lib
RL_INC_DIR    := -I $(shell brew --prefix readline)/include

SRCS =	cmd_exec/cmd_main.c										\
		cmd_exec/cmd_srcs/main_utils_bonus.c					\
		cmd_exec/cmd_srcs/child_execution_bonus.c				\
		cmd_exec/cmd_srcs/libft_functions_bonus.c				\
		cmd_exec/cmd_srcs/split_path_bonus.c					\
		cmd_exec/cmd_srcs/main_pipe_creation.c					\
		cmd_exec/cmd_srcs/utils/first_command_utils.c			\
		cmd_exec/cmd_srcs/utils/last_command_utils.c			\
		cmd_exec/cmd_srcs/utils/single_quote_exec.c				\
		builtins/libft_functions.c								\
		builtins/functions/builtin_functions.c					\
		builtins/functions/utils/builtin_functions_utils.c		\
		builtins/functions/utils/mini_export_utils.c			\
		builtins/functions/utils/mini_unset_utils.c				\
		builtins/functions/utils/mini_echo_utils.c				\
		builtins/functions/utils/mini_export_existing_var.c		\
		builtins/functions/utils/mini_cd_utils.c				\
		builtins/functions/utils/mini_echo_check_var_utils.c	\
		heredoc/gnl.c											\
		heredoc/gnl_utils.c										\
		heredoc/heredoc.c										\
		heredoc/heredoc_utils.c									\
		heredoc/heredoc_execution.c								\
		heredoc/heredoc_env_var_handling_utils.c				\
		main_loop_utils.c										\
		main.c											

INCS = 	cmd_exec/cmd_include/pipex_bonus.h					\
		includes/minishell.h

OBJS = $(SRCS:.c=.o)

%.o : %.c $(PRINTF_PATH)$(PRINTF_NAME) $(INCS)
		$(CC) $(FLAGS) $(RL_INC_DIR) -c $< -o $@

NAME = minishell

all : ft_printf $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(RL_LIB_DIR) $(FLAGS) -L $(PRINTF_PATH) -lftprintf -lreadline -o $(NAME) $(OBJS)

ft_printf :
	make -C $(PRINTF_PATH)

$(PRINTF_PATH)$(PRINTF_NAME) : ft_printf

clean : 
	rm -f $(OBJS)
	make clean -C $(PRINTF_PATH)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(PRINTF_PATH)

re : fclean all

.PHONY : all clean fclean re ft_printf