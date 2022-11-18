/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:12:28 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 13:37:02 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../parsing/parsing.h"
# include "../parsing/libft/libft.h"
# include "../ft_printf/includes/ft_printf.h"

# define READ 0
# define WRITE 1
# define BUF_SIZE 100
# define BUFFER_SIZE 1

typedef struct heredoc
{
	char	*env_var;
	char	*env_var_value;
	char	*limiter;
	int		var_length;
	int		delimiter_quotes;
	int		hd_pid;
	int		position;
	int		bkslash_check;
	int		check;
	int		flag;
	int		index;
	char	**envp;
	t_node	*tmp;
}	t_heredoc;

typedef struct exec
{
	int		last_cmd_outfile_check;
	int		first_cmd_squotes_check;
	int		infile_check;
	int		outfile_check;
	int		pipe_check;
	int		append_check;
	char	*infile_fd;
	char	*outfile_fd;
	char	*first_cmd_test;
	char	*last_cmd_test;
}	t_exec;

typedef struct env
{
	char	*path;
	char	*arg1;
	char	*arg2;
	char	**tab1;
	char	**tab2;
	char	**tab3;
	char	**param_tab1;
	char	**param_tab2;
	char	**param_tab3;
}	t_env;

typedef struct data
{
	int			envp_size;
	int			echo_arg;
	int			var_position;
	int			echo_sq_check;
	int			check_print_var;
	int			new_env_check;
	int			unset_env_check;
	int			tmp_count;
	int			first_cd_check;
	int			oldpwd_if;
	int			main_pid;
	int			pipe_check;
	int			infile_check;
	int			outfile_check;
	int			pipefd_tmp;
	int			cmd_nb;
	int			pid;
	int			**pipefd;
	int			**hd_pipefd;
	int			input_fd;
	int			output_fd;
	int			index;
	int			pipe_id;
	int			first_cmd_pid;
	int			last_cmd_pid;
	int			check_hd;
	int			heredoc_nb;
	int			hd_pipe_id;
	int			hd_id;
	int			*hd_pid;
	int			p_status;
	int			lst_size;
	int			nb_of_args;
	int			size_ptab1;
	int			size_ptab2;
	int			size_ptab3;
	int			pipe_nb;
	int			builtin_cmd_nb;
	int			check_main;
	int			new_env_size;
	int			unset_env_size;
	int			check_loop_export;
	int			index_arg;
	int			new_size;
	int			i;
	int			*test;
	int			consecutive_pipes;
	char		*builtins_name[7];
	char		buff[BUF_SIZE];
	char		buff_oldpwd[BUF_SIZE];
	char		**new_env;
	char		**unset_env;
	char		**no_env;
	char		**builtin_name;
	char		*name;
	char		*value;
	char		*var_name;
	char		*path;
	char		*str;
	char		*var_search;
	char		*echo_var;
	char		*hd_limit;
	char		*oldpwd;
	char		*cwd;
	char		*var_export;
	char		**envp;
	char		*home_path;
	char		*echo_file;
	char		*tmp_fill_tab;
	t_heredoc	hd;
	t_env		env;
	t_exec		exec;
}	t_data;

/* HEREDOC */
t_node		*search_first_hd(t_data *data, t_node *tmp, t_shell *parse,
				t_node **in);

void		eof_handler_hd(t_data *data, char *input, int output_fd);
void		heredoc(t_data *data, t_node *tmp);
void		close_hd_pipe(t_data *data, int i);
void		output_redirection(t_data *data);
void		print_heredoc(int output_fd);
void		sighandler_hd(int signum);
void		signal_tmp(int tmp);

char		*var_found(t_data *data, char *envp[], char *var_name, int i);
char		*getenv_hd(char *envp[], t_data *data, char *var_name);
char		*ft_itoa(int n);

int			heredoc_loop(t_data *data, t_node **infile_tmp, t_shell *parse,
				int ptr);
int			check_and_print_var_hd(char *str, t_data *data, int out_fd,
				int size);
int			cpvhd_specific_cases(t_data *data, char *str, int i, int output_fd);
int			print_var_hd(t_data *data, int var_size, char *var, int output_fd);
int			heredoc_exec(t_data *data, t_node **infile_tmp, t_shell *parse);
int			print_var_util(t_data *data, char *str, int i, int output_fd);
int			heredoc_main(t_data *data, t_node ***intab, t_shell *parse);
int			heredoc_process(t_node *tmp, t_data *data, int i, int ptr);
int			check_var_exists(int j, t_data *data, int output_fd);
int			search_hd(t_node *tmp, t_shell *parse, t_node **tab);
int			backslash_check(t_data *data, char *str, int i);
int			check_delimiter(char *str, char *delimiter);
int			check_delimiter(char *str, char *delimiter);
int			check_special_char_second_loop(char c);
int			check_special_char(char c, int size);
int			check_for_append(t_node *infile_tmp);
int			check_eof(char *str, char *limiter);
int			var_exists_hd(t_data *data);

/* COMMAND UTILS */
t_node		*main_init_check(t_data *data, t_shell *minishell, t_node *node);
t_node		*loop_to_first_arg(t_node *node, int i, int index);

void		free_and_exit_builtin(char **arg_tab, char **param, int p_size);
void		execution(t_data *data, t_shell *parse, t_node *node,
				int (*builtins[7])(t_data *, t_node *), int *gstatus);
void		first_command(t_data *data, t_node *node, t_shell *parse,
				int (*builtins[7])(t_data *, t_node *), int g);
void		last_command(t_data *data, t_node *node, t_shell *parse,
				int (*builtins[7])(t_data *, t_node *), int g);
void		command_exec(t_data *data, t_node *node, t_shell *parse,
				int (*builtins[7])(t_data *, t_node *), int g);
void		*commands(t_data *data, t_node *node, t_shell *parse,
				int (*builtins[7])(t_data *, t_node *), int g);
void		exec_main(t_data *data, t_node *node, t_shell *parse,
				int (*builtins[7])(t_data *, t_node *), int g);
void		exec_cmd(char **tab, char **param, t_data *data);
void		cmd_exec(t_data *data, t_shell *minishell,
				int (*builtins[7])(t_data *, t_node *));
void		cmd_execution(t_data *data, int pipe_id, t_node *node,
				int (*builtins[7])(t_data *, t_node *), int g);
void		cmd_exec_init(t_data *data, t_shell *parse_data);
void		first_cmd_execution(t_data *data, t_node *node,
				int (*builtins[7])(t_data *, t_node *), int g);
void		close_pipe_child_processes(t_data *data, int i);
void		main_init_before_loop(t_data *data, char **envp,
				int (*builtins[5])(t_data *data, t_node *node), int argc,
				char **argv);
void		last_cmd_execution(t_data *data, t_node *node,
				int (*builtins[5])(t_data *, t_node *), int g);
void		close_pipe_hd_before_dup(t_data *data, t_shell *parse);
void		eof_handler(char *input, t_shell *minishell);
void		*node_rotation(t_node *node, t_data *data);
void		cmd_exec_path(t_data *data, int pipe_id);
void		envp_check(t_data *data, char **envp);
void		sigint_handler_in_process(int signum);
void		sigint_handler_main_loop(int signum);
void		init_main(t_data *data, char **envp);
void		exit_cmd_not_found(char **param);
void		close_pipe(t_data *data, int i);
void		free_param_tab(t_data *data);
void		check_file(char *file);
void		sigtest(int signum);

char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		**fill_param_tab(t_node *node, t_data *data, char **tab);
char		**get_path(char *env[], t_data *data, char **args);
char		**join_arg(char **tab, char **args);
char		**ft_split(const char *s, char c);
char		**free_tab(char **tab, int i);

int			builtins_loop(char *tab_name[5],
				int (*builtins[5])(t_data *, t_node *),
				t_node *node, t_data *data, int *g);
int			heredoc_main(t_data *data, t_node ***intab, t_shell *parse);
int			start_heredoc(t_data *data, t_shell *parse, t_node *node);
int			export_and_unset(t_data *data, t_node *node, int check);
int			check_inputfile_last_cmd(t_data *data, t_shell *parse);
int			check_outfile_last_cmd(t_data *data, t_shell *parse);
int			iterate_outfile_cmd(t_data *data, t_shell *parse);
int			multi_cmd_dup_to_pipe(t_data *data, int index);
int			check_inputfile(t_data *data, t_shell *parse);
int			pipe_creation(t_data *data, int nbr_of_pipe);
int			check_outfile(t_data *data, t_shell *parse);
void		iterate_outfile_hd(t_shell *parse, int i);
int			export_exec(t_data *data, t_node *node);
int			unset_exec(t_data *data, t_node *node);
int			set_p_status(int status, t_node *node);
int			append_check(t_shell *p, int size);
int			check_loop_exec(char *str, int i);
int			ft_printf(const char *flags, ...);
int			**free_inttab(int **tab, int i);
int			check_loop(char *str, int j);
int			check_sq_cmd(char *cmd);
int			fork_creation(int pid);
int			check_pipe(char *str);

/* BUILTIN FUNCTIONS */
int			mini_export(t_data *data, char *var);
int			mini_unset(t_data *data, char *var);
int			mini_echo(t_data *data, t_node *node);
int			mini_exit(t_data *data, t_node *node);
int			mini_env(t_data *data, t_node *node);
int			mini_pwd(t_data *data, t_node *node);
int			mini_cd(t_data *data, t_node *node);

/* BUILTIN FUNCTIONS UTILS */
void		*echo_arg_newline_check(t_data *data, t_node *node, int check,
				int loop);
void		copy_loop(t_data *data, char *var_export, int new_size);
void		opendir_test(char *str, DIR *dir, struct dirent *pdir);
void		print_var(int j, t_data *data);
void		free_unset_tab(t_data *data);
void		sighandler(int signum);
void		free_old(char **tab, int size);

char		**newtab_malloc(t_data *data, int old_size, char **env, char *var);
char		*check_and_return_var(t_data *data, char **envp, char *var, int i);
char		**new_tab_copy(t_data *data, char *envp[], int i, int old_size);
char		*mini_getenv(char *envp[], t_data *mini_data, char *var_name);
char		**new_tab_with_existing_var(t_data *data, char *var_export);
char		*oldpwd_copy(t_data *data, char *str, int size);
char		**free_tab(char **tab, int i);
char		*get_var_name(char *var);

int			check_length(t_data *data, size_t size, int position, char *str);
int			check_var_exists_export(t_data *data, char *var_export);
int			specific_cases_with_special_char(t_data *data, int i);
int			var_search_copy(t_data *data, int size, int i, int j);
int			export_loop(t_node *n, t_data *data);
int			unset_var(int index, t_data *data, char *var_unset);
int			malloc_and_cpy(t_data *data, int i, int index);
int			check_nb_of_args(t_node *node, int size);
int			write_and_check_signs(int i, t_data *data);
int			check_var_hd(char *str, char *var_name);
int			path_exists(t_data *data, t_node *node);
int			check_var(char *str, char *var_name);
int			check_special_char(char c, int size);
int			pid_display(t_data *data, int i);
int			check_signs(int i, t_data *data);
int			envp_size_for_tmp(char **tab);
int			display_export(t_data *data);
int			update_old_pwd(t_data *data);
int			check_if_empty(t_data *data);
int			check_oldpwd(t_data *data);
int			newline_arg(t_data *data);
int			update_pwd(t_data *data);
int			check_remains(char *str);
int			no_path(t_data *data);
int			no_args(t_node *node);

/* GNL FUNCTIONS */
size_t		ft_strlen_gnl(char *s);
size_t		ft_strnlen(char *s);

/* MAIN UTILS FUNCTIONS */
t_node		*node_rotation_exec(t_node *node, t_shell *parse);

void		init_builtins_tab(char *builtins_name[5],
				int (*builtins[7])(t_data *, t_node *));
void		free_all(t_shell *minishell);

int			export_no_env(t_data *data);

#endif