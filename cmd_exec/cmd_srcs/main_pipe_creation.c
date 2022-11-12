/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:44:50 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/12 15:34:38 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pipe_creation(t_data *data, int nb_of_pipe)
{
	int	i;

	i = 0;
	if (nb_of_pipe > 0)
	{
		data->pipefd = malloc(sizeof(int *) * (nb_of_pipe - 1));
		if (!data->pipefd)
			return (0);
	}
	while (i < nb_of_pipe)
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
