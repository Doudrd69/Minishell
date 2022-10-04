/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:04:20 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/09/27 15:02:27 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"

int	hd_pipe_creation(t_data *data)
{
	int	i;

	i = 0;
	if (data->check_hd == 1)
	{
		data->hd_pipefd = malloc(sizeof(int *) * data->heredoc_nb);
		if (!data->hd_pipefd)
			return (0);
		while (i < data->heredoc_nb)
		{
			data->hd_pipefd[i] = malloc(sizeof(int) * 2);
			if (!data->hd_pipefd[i])
			{
				free_inttab(data->hd_pipefd, i);
				return (0);
			}
			if (pipe(data->hd_pipefd[i]) == -1)
			{
				perror("pipe");
				return (0);
			}
			i++;
		}
	}
	return (i);
}

int	heredoc_exec(t_data *data)//probleme car alterne entre les differents hd
{
	int	i;
	int	ptr;
	int	pipe_nb;

	i = 0;
	pipe_nb = hd_pipe_creation(data);
	(void)pipe_nb;
	data->hd_pid = malloc(sizeof(int) * data->heredoc_nb);
	if (!data->hd_pid)
		return (1);
	while (i < data->heredoc_nb)
	{
		data->hd_pid[i] = fork();
		if (data->hd_pid[i] == -1)
		{
			printf("Error while creating heredoc process\n");
			return (1);
		}
		if (data->hd_pid[i] == 0)
			heredoc(data);
		waitpid(data->hd_pid[i], &ptr, 0);
		data->hd_pipe_id++;
		data->hd_id++;
		i++;
	}
	return (0);
}
