/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:44:50 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/02 13:50:08 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_include/pipex_bonus.h"

int	pipe_creation(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd_nb > 1)
	{
		data->pipefd = malloc(sizeof(int *) * (data->cmd_nb - 1));
		if (!data->pipefd)
			return (0);
	}
	while (i < data->cmd_nb - 1)
	{
		data->pipefd[i] = malloc(sizeof(int) * 2);
		if (!data->pipefd[i])
		{
			free_inttab(data->pipefd, i);
			return (0);
		}
		if (pipe(data->pipefd[i]) == -1)
		{
			perror("pipe");
			return (0);
		}
		i++;
	}
	return (i);
}
