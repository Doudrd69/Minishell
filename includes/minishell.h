/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:12:28 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/09/28 09:48:10 by ebrodeur         ###   ########lyon.fr   */
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

# define BUF_SIZE 50
# define BUFFER_SIZE 1

typedef struct mini_data
{
	char		buff[BUF_SIZE];
	char		*home_path;
	char		**new_env;
	char		**unset_env;
	char		**builtin_name;
	int			envp_size;
	int			echo_arg;
	int			var_position;		//pour le mini_export quand la var existe deja
	int			echo_sq_check;
	char		*name;
	char		*value;
	char		*var_name;
	char		*path;
	char		*str;
	char		**env;
	char		*var_search;
	char		*echo_var;
	char		*hd_limit;
	int			check_print_var;
	int			*p_status;
	int			new_env_check;
	int			unset_env_check;
}	t_mini_data;

/* BUILTIN FUNCTIONS */
int		mini_export(t_mini_data *data);
int		mini_unset(t_mini_data *data);
int		mini_cd(t_mini_data *data);
int		mini_pwd(t_mini_data *data);
int		mini_echo(t_mini_data *data);
int		mini_env(t_mini_data *data);
int		mini_exit();

/* BUILTIN FUNCTIONS UTILS */
char	**new_tab_malloc(t_mini_data *data, int old_tab_size, char *envp[], char *name, char *value);
char	**new_tab_copy(t_mini_data *data, char *envp[], int i, int old_tab_size);
char	**new_var_tab_copy(t_mini_data *data, int i, char *name, char *value);
char	*mini_getenv(char *envp[], t_mini_data *mini_data, char *var_name);
int		malloc_and_cpy(t_mini_data *data, int i, int index);
void	opendir_test(char *str, DIR *dir, struct dirent *pdir);
int		write_and_check_signs(int i, t_mini_data *data);
char	**new_tab_with_existing_var(t_mini_data *data);
int 	check_var_exists_export(t_mini_data *data);
int		unset_var(int index, t_mini_data *data);
int		check_signs(int i, t_mini_data *data);
int		check_var(char *str, char *var_name);
char	**free_tab(char **tab, int i);
int		check_remains(char *str);

/* LIBFT FUNCTIONS */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_strlen(char *s);

/* MAIN UTILS FUNCTIONS */

#endif