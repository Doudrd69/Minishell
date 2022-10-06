/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:41:48 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/06 11:09:06 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"
#include <readline/readline.h>

void	sighandler_hd()
{
	//il faut quitter le process du HD et ne pas executer
	exit(0);
}

int	check_delimiter(char *str, char *delimiter)
{
	size_t	size;

	size = 0;//pour pas prendre le >
	while (str[size])
		size++;
	if (size == ft_strlen(delimiter))
		return (0);
	return (1);
}


int	var_exists_hd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->envp_size)
	{
		if (ft_strnstr(data->envp[i], data->hd.env_var, ft_strlen(data->hd.env_var)))
		{
			if (check_var(data->envp[i], data->hd.env_var))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_var_exists(int j, t_data *data, int output_fd)
{
	int	size;
	int	i;

	i = 0;
	if (var_exists_hd(data) == 0)
	{
		j = 0;
		data->hd.env_var_value = getenv_hd(data->envp, data, data->hd.env_var);
		while (data->hd.env_var_value[j] != '=')
			j++;
		size = ft_strlen(&data->hd.env_var_value[j]);
		while (i < size - 1)
		{
			if (output_fd != 0 && output_fd != 1)
				write(output_fd, &data->hd.env_var_value[++j], 1);
			i++;
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
	int	size;
	
	signal(SIGINT, &sighandler_hd);
	data->hd.hd_pid = getpid();
	output_fd = data->hd_pipefd[data->hd_pipe_id][WRITE];
	while (1)
	{
		size = 0;
		str = readline("> ");
		eof_handler(str);
		while (str[size])
			size++;
		if (check_and_print_var_hd(str, data, output_fd, size) == 0)
		{
			if ((ft_strncmp(str, "test", 4) == 0))
			{
				if (check_delimiter(str, "test") == 0)//si cat, je return (0), sinon je return le print heredoc qui aura ecrit dans le fichier d'output
				{
					free(str);
					// if (data->home_path)
					// 	free(data->home_path);
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