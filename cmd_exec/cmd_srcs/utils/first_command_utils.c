/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:56:41 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/02 17:24:33 by ebrodeur         ###   ########lyon.fr   */
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

int	input_file_opening(t_data *data, t_shell *parse)
{
	while (parse->tab_infile[0]->next != NULL)
		parse->tab_infile[0] = parse->tab_infile[0]->next;
	data->input_fd = open(parse->tab_infile[0]->content, O_RDONLY);
	if (data->input_fd < 0)
	{
		ft_printf("minishell: %s: No such file or directory\n",
			parse->tab_infile[0]->content);
		return (1);
	}
	if (dup2(data->input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}

int	check_inputfile(t_data *data, t_shell *parse)
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
	if (parse->nbr_infile > 0)
		*data->p_status = input_file_opening(data, parse);
	data->input_fd = STDIN_FILENO;
	return (0);
}

int	iterate_outfile(t_shell *parse)
{
	int	i;

	i = 0;
	while (i < parse->nbr_outfile)
	{
		printf("==> %s\n", parse->tab_outfile[0]->content);
		if (i == parse->nbr_outfile - 1)
			return (open(parse->tab_outfile[0]->content, O_WRONLY | O_TRUNC
					| O_CREAT, 0666));
		open(parse->tab_outfile[0]->content, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		parse->tab_outfile[0] = parse->tab_outfile[0]->next;
		i++;
	}
	return (-1);
}

int	check_outfile(t_data *data, t_shell *parse)
{
	if (parse->nbr_outfile > 0 && parse->nbr_pipe == 0)
	{
		data->output_fd = iterate_outfile(parse);
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
