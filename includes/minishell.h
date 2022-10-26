/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:12:28 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/26 14:40:58 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../cmd_exec/cmd_include/pipex_bonus.h"
# include "../parsing/parsing.h"
# include "../parsing/libft/libft.h"

# define BUF_SIZE 100
# define BUFFER_SIZE 1

typedef struct mini_data
{
	int			envp_size;
	int			echo_arg;
	int			var_position;
	int			echo_sq_check;
	int			check_print_var;
	int			*p_status;
	int			new_env_check;
	int			unset_env_check;
	int			tmp_count;
	int			first_cd_check;
	int			oldpwd_if;
	int			main_pid;
	int			pipe_check;
	char		buff[BUF_SIZE];
	char		buff_oldpwd[BUF_SIZE];
	char		*home_path;
	char		**new_env;
	char		**unset_env;
	char		**no_env;
	char		**builtin_name;
	char		*name;
	char		*value;
	char		*var_name;
	char		*path;
	char		*str;
	char		**env;
	char		*var_search;
	char		*echo_var;
	char		*hd_limit;
	char		*oldpwd;
	char		*cwd;
	char		*var_export;
}	t_mini_data;

/* BUILTIN FUNCTIONS */
int		mini_export(t_mini_data *data, char *var_export);
int		mini_unset(t_mini_data *data, char *var_unset);
int		mini_echo(t_mini_data *data, t_node *node);
int		mini_env(t_mini_data *data, t_node *node);
int		mini_pwd(t_mini_data *data, t_node *node);
int		mini_cd(t_mini_data *data, t_node *node);
int		mini_exit();

/* BUILTIN FUNCTIONS UTILS */
void	*echo_arg_newline_check(t_mini_data *data, t_node *node, int check, int loop);
void	opendir_test(char *str, DIR *dir, struct dirent *pdir);
void	copy_loop(t_mini_data *data, char *var_export);
void	print_var(int j, t_mini_data *data);
void	sighandler(int signum);

char	**newtab_malloc(t_mini_data *data, int old_size, char **env, char *var);
char	*check_and_return_var(t_mini_data *data, char **envp, char *var, int i);
char	**new_var_tab_copy(t_mini_data *data, int i, char *name, char *value);
char	**new_tab_copy(t_mini_data *data, char *envp[], int i, int old_size);
char	*mini_getenv(char *envp[], t_mini_data *mini_data, char *var_name);
char	**new_tab_with_existing_var(t_mini_data *data, char *var_export);
char	**free_tab(char **tab, int i);
char	*get_var_name(char *var);

int		check_var_exists_export(t_mini_data *data, char *var_export);
int		specific_cases_with_special_char(t_mini_data *data, int i);
int		var_search_copy(t_mini_data *data, int size, int i, int j);
int		unset_var(int index, t_mini_data *data, char *var_unset);
int		malloc_and_cpy(t_mini_data *data, int i, int index);
int		write_and_check_signs(int i, t_mini_data *data );
int		path_exists(t_mini_data *data, t_node *node);
int		pid_display(t_mini_data *data, int i);
int		check_signs(int i, t_mini_data *data);
int		check_var(char *str, char *var_name);
int		check_special_char(char c, int size);
int		update_old_pwd(t_mini_data *data);
int		check_if_empty(t_mini_data *data);
int		check_oldpwd(t_mini_data *data);
int		update_pwd(t_mini_data *data);
int		no_path(t_mini_data *data);
int		check_remains(char *str);

/* GNL FUNCTIONS */
size_t	ft_strlen_gnl(char *s);
size_t	ft_strnlen(char *s);

/* MAIN UTILS FUNCTIONS */
void	init_builtins_tab(char *builtins_name[5], int (*builtins[5])(t_mini_data *, t_node *));
void	free_all(t_shell *minishell);

int		export_no_env(t_mini_data *data);

#endif