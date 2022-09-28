/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:41:48 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/09/28 10:31:39 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"
#include <readline/readline.h>

int	check_delimiter(char *str, char *delimiter)
{
	size_t	size;

	size = 0;//pour pas prendre le >
	while (str[size])
		size++;
	if ((size - 1) == ft_strlen(delimiter))
		return (0);
	return (1);
}


int	var_exists_hd(char *var, char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], var, ft_strlen(var)))
		{
			if (check_var(envp[i], var))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_var_exists(int j, t_data *data, int output_fd)
{
	if (var_exists_hd(data->hd.env_var, data->envp) == 0)
	{
		j = 0;
		data->hd.env_var_value = getenv_hd(data->envp, data, data->hd.env_var);
		while (data->hd.env_var_value[j] != '=')
			j++;
		while (data->hd.env_var_value[++j])
		{
			if (output_fd != 0 && output_fd != 1)
				write(output_fd, &data->hd.env_var_value[j], 1);
		}
		free(data->hd.env_var);
		return (0);
	}
	free(data->hd.env_var);
	return (1);
}

void heredoc(t_data *data)
{
	char *str = NULL;
	int output_fd;

	data->hd.hd_pid = getpid();
	output_fd = data->hd_pipefd[data->hd_pipe_id][WRITE];
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(data->input_fd);
		if (check_and_print_var_hd(str, data, output_fd) == 0)
		{
			if ((ft_strncmp(str, "test", 4) == 0))
			{
				if (check_delimiter(str, "test") == 0)//si cat, je return (0), sinon je return le print heredoc qui aura ecrit dans le fichier d'output
				{
					free(str);
					free(data->home_path);
					close(output_fd);
					close(data->hd_pipefd[data->hd_pipe_id][READ]);
					exit(0);
				}
			}
		}
		free(str);
	}
	return ;
}
//si on fait un ctrl D il faut supprimer le fichier
//leaks auqnd on lance plusieurs HD