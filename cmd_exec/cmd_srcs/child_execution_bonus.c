/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:43:54 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/17 14:11:18 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_include/pipex_bonus.h"

void	first_cmd_execution(t_data *data, char *envp[])
{
	if (access(data->env.param_tab1[0], X_OK) == 0)//on verifie l'acces au cas ou on recup directement un chemin
	{
		if (data->exec.pipe_check == 1)
			close_pipe(data, (data->cmd_nb - 2));//close de pipe s'il y en a
		if (data->exec.infile_check == 1)
			close(data->input_fd);//on le close que s'il existe (INFILE)
		if (data->exec.outfile_check == 1)
			close(data->output_fd);//on le close que s'il existe (OUTFILE)
		if (data->hd_pipefd)
			close_hd_pipe(data, data->heredoc_nb - 1);
		if (execve(data->env.param_tab1[0], data->env.param_tab1, envp) == -1)
			perror("execve");
	}
	else
	{
		if (data->env.tab1 != NULL)
			data->env.tab1 = join_arg(data->env.param_tab1, data->env.tab1);
		if (data->exec.pipe_check == 1)
			close_pipe(data, (data->cmd_nb - 2));//close de pipe s'il y en a
		if (data->exec.infile_check == 1)
			close(data->input_fd);//on le close que s'il existe (INFILE)
		if (data->exec.outfile_check == 1)
			close(data->output_fd);//on le close que s'il existe (OUTFILE)
		if (data->hd_pipefd)
			close_hd_pipe(data, data->heredoc_nb - 1);
		exec_cmd(data->env.tab1, data->env.param_tab1, envp, data);
	}
}

void	last_cmd_execution(t_data *data, char *envp[])
{
	if (access(data->env.param_tab2[0], X_OK) == 0)
	{
		close_pipe(data, (data->cmd_nb - 2));
		close(data->output_fd);
		if (execve(data->env.param_tab2[0], data->env.param_tab2, envp) == -1)
			perror("execve");
	}
	else
	{
		if (data->env.tab2 != NULL)
			data->env.tab2 = join_arg(data->env.param_tab2, data->env.tab2);
		if (data->exec.pipe_check == 1)
			close_pipe(data, (data->cmd_nb - 2));
		if (data->exec.outfile_check == 1)
			close(data->output_fd);
		if (data->hd_pipefd)
			close_hd_pipe(data, data->heredoc_nb - 1);
		exec_cmd(data->env.tab2, data->env.param_tab2, envp, data);
	}
}

void	cmd_execution(t_data *data, char *envp[], int pipe_id)
{
	if (access(data->env.param_tab3[0], X_OK) == 0)
	{
		close_pipe(data, pipe_id);
		if (execve(data->env.param_tab3[0], data->env.param_tab3, envp) == -1)
			perror("execve");
	}
	else
	{
		if (data->env.tab3 != NULL)
			data->env.tab3 = join_arg(data->env.param_tab3, data->env.tab3);
		if (pipe_id != (data->cmd_nb - 2))
			close_pipe(data, pipe_id + 1);
		else
			close_pipe(data, pipe_id);
		if (data->hd_pipefd)
			close_hd_pipe(data, data->heredoc_nb - 1);
		exec_cmd(data->env.tab3, data->env.param_tab3, envp, data);
	}
}
