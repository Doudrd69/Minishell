/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:04:20 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/17 20:12:53 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*getenv_hd(char *envp[], t_data *data, char *var_name)
{
	if (ft_strnstr(envp[data->hd.position], var_name, ft_strlen(var_name)))
		return (var_found(data, envp, var_name, data->hd.position));
	ft_printf("Cannot find %s\n", var_name);
	return (NULL);
}

void	output_redirection(t_data *data)
{
	if (dup2(data->hd_pipefd[data->hd_pipe_id][WRITE], STDOUT_FILENO == -1))
	{
		perror("dup2");
		return ;
	}
	return ;
}

void	close_hd_pipe(t_data *data, int i)
{
	while (i >= 0)
	{
		close(data->hd_pipefd[i][READ]);
		close(data->hd_pipefd[i][WRITE]);
		i--;
	}
	return ;
}

int	hd_pipe_creation(t_data *data)
{
	int	i;

	i = 0;
	if (data->check_hd == 1)
	{
		data->hd_pipefd = malloc(sizeof(int *) * data->heredoc_nb);
		if (!data->hd_pipefd)
			return (1);
		while (i < data->heredoc_nb)
		{
			data->hd_pipefd[i] = malloc(sizeof(int) * 2);
			if (!data->hd_pipefd[i])
			{
				free_inttab(data->hd_pipefd, i);
				return (1);
			}
			if (pipe(data->hd_pipefd[i]) == -1)
			{
				perror("pipe");
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	heredoc_exec(t_data *data, t_node **infile_tmp, t_shell *parse)
{
	int	i;
	int	ptr;

	i = -1;
	ptr = 0;
	data->hd.flag = 0;
	data->hd.index = 0;
	data->i = -1;
	if (hd_pipe_creation(data) == 1)
		return (1);
	data->hd_pid = malloc(sizeof(int) * data->heredoc_nb);
	if (!data->hd_pid)
		return (1);
	if (heredoc_loop(data, infile_tmp, parse, ptr) == 1)
		return (1);
	return (0);
}
