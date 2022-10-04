/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:22:52 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/09/29 16:27:29 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# define READ 0
# define WRITE 1

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../ft_printf/includes/ft_printf.h"
# include "../../ft_printf/includes/ft_sort_params.h"
# include "../../includes/minishell.h"

typedef struct heredoc
{
	char	*env_var;
	char	*env_var_value;
	int		var_length;
	int		delimiter_quotes;
	int		hd_pid;
	char	**envp;
}	t_heredoc;

typedef struct exec
{
	int		last_cmd_outfile_check;
	int		first_cmd_squotes_check;
	int		infile_check;
	int		outfile_check;
	int		pipe_check;
	int		append_check;
	char	*infile_fd;//pointeur sur le fichier
	char	*outfile_fd;//pointeur sur le fichier
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
	int		cmd_nb;
	int		pid;
	int		**pipefd;
	int		**hd_pipefd;
	int		input_fd;
	int		output_fd;
	int		index;
	int		pipe_id;
	int		first_cmd_pid;
	int		last_cmd_pid;
	int		envp_size;
	int		check_hd;
	int		heredoc_nb;
	int		hd_pipe_id;
	int		hd_id;
	int		*hd_pid;
	int		*p_status;
	char	**envp;
	char	*home_path;
	t_heredoc	hd;
	t_env	env;
	t_exec	exec;
}	t_data;

/* HEREDOC */
int		print_var_hd(t_data *data, int var_size, char *var, int output_fd);
int		check_and_print_var_hd(char *str, t_data *data, int output_fd, int size);
char	*getenv_hd(char *envp[], t_data *data, char *var_name);
int		check_var_exists(int j, t_data *data, int output_fd);
int		check_delimiter(char *str, char *delimiter);
int		var_exists_hd(char *var, char *envp[]);
void	close_hd_pipe(t_data *data, int i);
void	output_redirection(t_data *data);
void	print_heredoc(int output_fd);
int		heredoc_exec(t_data *data);
void	heredoc(t_data *data);
char	*get_next_line(int fd);

/* COMMAND UTILS */
int		check_outfile(t_data *data);
int		check_outfile_last_cmd(t_data *data);
int		check_inputfile(t_data *data);

void	command_exec(t_data *data, char *envp[], int cmd_id);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	last_command(char *envp[], t_data *data);
void	first_command(char *envp[], t_data *data);
void	cmd_execution(t_data *data, char *envp[], int pipe_id);
char	**get_path(char *env[], t_data *data, char **args);
void	commands(t_data *data, char *argv[], char *envp[]);
void	exec_cmd(char **tab, char **param, char *env[], t_data *data);
void	first_cmd_execution(t_data *data, char *envp[]);
void	close_pipe_child_processes(t_data *data, int i);
void	last_cmd_execution(t_data *data, char *envp[]);
char	**join_arg(char **tab, char **args);
char	**ft_split(const char *s, char c);
int		ft_printf(const char *flags, ...);
char	*ft_strjoin(char *s1, char *s2);
int		**free_inttab(int **tab, int i);
void	close_pipe(t_data *data, int i);
char	**free_tab(char **tab, int i);
int		pipe_creation(t_data *data);
int		check_sq_cmd(char *cmd);
size_t	ft_strlen(char *s);

#endif