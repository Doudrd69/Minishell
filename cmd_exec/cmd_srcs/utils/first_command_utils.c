/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 12:56:41 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/09 13:32:19 by ebrodeur         ###   ########lyon.fr   */
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

int	check_inputfile(t_data *data, t_shell *parse)//il faut check si j'ai des HD + des inputfile
{
	if (parse->nbr_infile > 0 || parse->nbr_appendin > 0)
	{
		while (parse->tab_infile[0]->next != NULL)
			parse->tab_infile[0] = parse->tab_infile[0]->next;
		if (data->check_hd == 1 && (parse->tab_infile[0]->type == 'A'))
		{
			if (parse->infile_size > 0)
				data->hd_pipe_id = data->hd_pipe_id - parse->nbr_appendin;
			else
				data->hd_pipe_id -= 1;
			if (dup2(data->hd_pipefd[data->hd_pipe_id][READ], STDIN_FILENO) == -1)
			{
				perror("dup2");
				return (1);
			}
			return (0);
		}
		if (parse->tab_infile[0]->type == 'C')
			*data->p_status = input_file_opening(data, parse);
		data->input_fd = STDIN_FILENO;
	}
	return (0);
}

int	iterate_outfile(t_shell *parse)
{
	while (parse->tab_outfile[0] != NULL)
	{
		if (parse->tab_outfile[0]->next == NULL)
		{
			if (parse->tab_outfile[0]->type == 'C')
				return (open(parse->tab_outfile[0]->content, O_WRONLY | O_TRUNC
					| O_CREAT, 0666));
			else
				return (open(parse->tab_outfile[0]->content, O_WRONLY | O_APPEND | O_CREAT, 0666));
		}
		if (parse->tab_outfile[0]->type == 'C')
			open(parse->tab_outfile[0]->content, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else
			open(parse->tab_outfile[0]->content, O_WRONLY | O_APPEND | O_CREAT, 0666);
		parse->tab_outfile[0] = parse->tab_outfile[0]->next;
	}
	return (-1);
}

int	check_outfile(t_data *data, t_shell *parse)
{
	if ((parse->nbr_outfile > 0 || parse->nbr_appendout > 0) && parse->tab_outfile[0])
	{
		data->output_fd = iterate_outfile(parse);
		if (data->output_fd < 0)
		{
			ft_printf("Error : can't open file : %s\n", parse->tab_outfile[0]->content);
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
