/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipe_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 10:44:50 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/26 11:26:11 by ebrodeur         ###   ########lyon.fr   */
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

void	command_exec(t_data *data, t_node *node, char *envp[], int cmd_id)
{
	(void)cmd_id;
	if (dup2(data->pipefd[data->pipe_id - 1][READ], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return ;
	}
	data->env.tab3 = get_path(envp, data, data->env.tab3);
	data->env.param_tab3 = fill_param_tab(node, data, data->env.param_tab3);
	while (data->env.param_tab3[data->size_ptab3])
		data->size_ptab3++;
	if (dup2(data->pipefd[data->pipe_id][WRITE], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return ;
	}
	cmd_execution(data, envp, data->pipe_id);
}
