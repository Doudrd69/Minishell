/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 13:55:59 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 16:59:40 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd_path_last(t_data *data)
{
	if (data->exec.pipe_check == 1)
		close_pipe(data, (data->cmd_nb - 2));
	if (data->hd_pipefd)
		close_hd_pipe(data, data->heredoc_nb - 1);
	check_file(data->env.param_tab2[0]);
	if (execve(data->env.param_tab2[0], data->env.param_tab2,
			data->envp) == -1)
	{
		perror("execve");
		exit(errno);
	}
}

void	cmd_exec_path(t_data *data, int pipe_id)
{
	close_hd_pipe(data, data->heredoc_nb - 1);
	close_pipe(data, pipe_id);
	check_file(data->env.param_tab3[0]);
	if (execve(data->env.param_tab3[0], data->env.param_tab3,
			data->envp) == -1)
	{
		perror("execve");
		exit(errno);
	}
}

void	exec_cmd_path(t_data *data, char *envp[])
{
	if (data->exec.pipe_check == 1)
		close_pipe(data, (data->cmd_nb - 2));
	if (data->hd_pipefd)
		close_hd_pipe(data, data->heredoc_nb - 1);
	check_file(data->env.param_tab1[0]);
	if (execve(data->env.param_tab1[0], data->env.param_tab1, envp) == -1)
	{
		perror("execve");
		exit(errno);
	}
}
