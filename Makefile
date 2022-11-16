CC = gcc
FLAGS = -Werror -Wextra -Wall -fsanitize=address -g3

PRINTF_NAME = libftprintf.a
PRINTF_PATH = ft_printf/

LIBFT_NAME = libft.a
LIBFT_PATH = parsing/libft/

RL_LIB_DIR    := -L $(shell brew --prefix readline)/lib
RL_INC_DIR    := -I $(shell brew --prefix readline)/include

SRCS =	cmd_exec/cmd_main.c										\
		cmd_exec/cmd_srcs/utils/first_command_utils.c			\
		cmd_exec/cmd_srcs/utils/last_command_utils.c			\
		cmd_exec/cmd_srcs/utils/single_quote_exec.c				\
		cmd_exec/cmd_srcs/utils/multi_commands_utils.c			\
		cmd_exec/cmd_srcs/child_execution_bonus.c				\
		cmd_exec/cmd_srcs/main_pipe_creation.c					\
		cmd_exec/cmd_srcs/main_utils_bonus.c					\
		cmd_exec/cmd_srcs/split_path_bonus.c					\
		cmd_exec/cmd_srcs/fill_param_tab.c						\
		cmd_exec/cmd_srcs/child_exec_utils.c					\
		cmd_exec/cmd_main_utils.c								\
		builtins/functions/utils/mini_export_existing_var.c		\
		builtins/functions/utils/builtin_functions_utils.c		\
		builtins/functions/utils/mini_echo_newline_arg.c		\
		builtins/functions/utils/mini_cd_oldpwd_update.c		\
		builtins/functions/utils/mini_getenv_utils.c			\
		builtins/functions/utils/mini_export_utils.c			\
		builtins/functions/utils/export_exec_utils.c			\
		builtins/functions/utils/mini_unset_utils.c				\
		builtins/functions/utils/mini_echo_utils.c				\
		builtins/functions/builtin_export_unset.c				\
		builtins/functions/utils/mini_cd_utils.c				\
		builtins/functions/builtin_functions.c					\
		builtins/functions/display_export.c						\
		heredoc/heredoc_env_var_handling_utils.c				\
		heredoc/heredoc_execution_utils.c						\
		heredoc/heredoc_functions.c								\
		heredoc/heredoc_execution.c								\
		heredoc/heredoc_utils.c									\
		heredoc/heredoc.c										\
		parsing/srcs/check_quote_dollars.c						\
		parsing/srcs/ft_dlstadd_front.c							\
		parsing/srcs/dollars_include.c							\
		parsing/srcs/ft_dlstadd_back.c							\
		parsing/srcs/search_var_bis.c							\
		parsing/srcs/init_variable.c							\
		parsing/srcs/redirections.c								\
		parsing/srcs/search_var.c								\
		parsing/srcs/ft_dlstnew.c 								\
		parsing/debug/print_all.c								\
		parsing/srcs/pipe_bis.c									\
		parsing/srcs/counter.c									\
		parsing/srcs/parsing.c									\
		parsing/srcs/dollars.c									\
		parsing/srcs/quote.c									\
		parsing/srcs/exit.c										\
		parsing/srcs/path.c										\
		parsing/srcs/pipe.c										\
		parsing/srcs/space.c									\
		parsing/srcs/new_value_dollars.c						\
		parsing/srcs/search_infile.c							\
		parsing/srcs/search_heredoc.c							\
		parsing/srcs/search_outfile.c							\
		parsing/srcs/search_append.c							\
		parsing/srcs/split_minishell.c							\
		parsing/srcs/split_minishell_nbr_words.c				\
		parsing/srcs/split_minishell_malloc_ws.c				\
		parsing/srcs/parse_space_quote.c						\
		parsing/srcs/parse_quote_tab.c							\
		parsing/srcs/parse_quote_outab.c						\
		parsing/srcs/check_syntax_infile.c						\
		parsing/srcs/check_syntax_outfile.c						\
		parsing/srcs/check_syntax_append.c						\
		parsing/srcs/check_syntax_heredoc.c						\
		parsing/srcs/check_syntax_append_space.c				\
		parsing/srcs/check_syntax_outfile_space.c				\
		parsing/srcs/check_syntax_infile_space.c				\
		parsing/srcs/check_syntax_heredoc_space.c				\
		parsing/srcs/new_value_dollars_bis.c					\
		parsing/srcs/free_exit.c								\
		parsing/srcs/dollars_bis.c								\
		parsing/srcs/dollars_mod.c								\
		parsing/srcs/change_value_dquote.c						\
		parsing/srcs/dollars_mod_check.c						\
		parsing/srcs/parse_quote_outab_utils.c					\
		parsing/srcs/parse_quote_intab_utils.c					\
		parsing/srcs/parse_space_quote_utils.c					\
		parsing/srcs/split_minishell_get_filling.c				\
		parsing/srcs/check_syntax_pipe.c						\
		parsing/srcs/space_utils.c								\
		parsing/srcs/search_outfile_utils.c						\
		parsing/srcs/search_infile_utils.c						\
		parsing/srcs/search_heredoc_utils.c						\
		parsing/srcs/search_append_utils.c						\
		parsing/srcs/redirections_utils.c						\
		parsing/srcs/unstack_list.c								\
		parsing/srcs/free_all_exit.c							\
		parsing/srcs/search_redir_malloc.c						\
		main_functions/main_loop_utils.c						\
		main_functions/main_function.c							\
		main_functions/main_utils.c								\
		main_functions/free_parse.c								\
		main_functions/no_env.c									\
		main_functions/signal.c									\
		main_functions/main.c

INCS =	includes/minishell.h									\
		parsing/parsing.h

OBJS = $(SRCS:.c=.o)

%.o : %.c $(PRINTF_PATH)$(PRINTF_NAME) $(LIBFT_PATH)$(LIBFT_NAME) $(INCS) Makefile
		$(CC) $(FLAGS)  $(RL_INC_DIR) -c $< -o $@

NAME = minishell

all : ft_printf libft $(NAME)

$(NAME) : $(OBJS)
		$(CC) $(RL_LIB_DIR) $(FLAGS) -L $(PRINTF_PATH) -L $(LIBFT_PATH) -lftprintf -lft -lreadline -framework CoreFoundation -o $(NAME) $(OBJS)

ft_printf :
	make -j -C $(PRINTF_PATH)

libft :
	make -j FLAGS="$(FLAGS)" -C $(LIBFT_PATH)

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