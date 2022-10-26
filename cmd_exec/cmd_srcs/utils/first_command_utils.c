/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:56:41 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/26 15:10:23 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../cmd_include/pipex_bonus.h"

int	check_pipe_and_exec(t_data *data)
{
	if (data->exec.pipe_check == 0)
		return (0);
	else
	{
		if (dup2(data->pipefd[0][WRITE], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
	}
	return (0);
}

int	input_file_opening(t_data *data)
{
	data->input_fd = open(data->exec.infile_fd, O_RDONLY);
	if (data->input_fd < 0)
	{
		ft_printf("minishell: %s: No such file or directory\n",
			data->exec.infile_fd);
		return (1);
	}
	if (dup2(data->input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}

int	check_inputfile(t_data *data)
{
	if (data->check_hd == 1 && data->exec.infile_check == 0)
	{
		if (dup2(data->hd_pipefd[data->hd_pipe_id - 1][READ],
			STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		return (0);
	}
	if (data->exec.infile_check == 1)
		*data->p_status = input_file_opening(data);
	data->input_fd = STDIN_FILENO;
	return (0);
}

int	check_outfile(t_data *data)
{
	if (data->exec.outfile_check == 1)
	{
		if (data->exec.append_check == 1)
			data->output_fd = open(data->exec.outfile_fd, O_WRONLY | O_CREAT,
					0666);
		else
		{
			data->output_fd = open(data->exec.outfile_fd, O_WRONLY | O_TRUNC
					| O_CREAT, 0666);
		}
		if (data->output_fd < 0)
		{
			ft_printf("Error : can't open file :\n");
			return (1);
		}
		if (dup2(data->output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		return (0);
	}
	else
		return (check_pipe_and_exec(data));
}
