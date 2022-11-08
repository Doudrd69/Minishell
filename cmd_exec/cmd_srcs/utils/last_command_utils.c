/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:28:28 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/08 10:04:22 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../cmd_include/pipex_bonus.h"

int	iterate_outfile_lastcmd(t_shell *parse)
{
	int	size;

	size = parse->outfile_size;
	while (parse->tab_outfile[size] != NULL)
	{
		if (parse->tab_outfile[size]->next == NULL)
			return (open(parse->tab_outfile[size]->content, O_WRONLY | O_TRUNC | O_CREAT, 0666));
		open(parse->tab_outfile[size]->content, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		parse->tab_outfile[size] = parse->tab_outfile[size]->next;
	}
	return (-1);
}

int	check_outfile_last_cmd(t_data *data, t_shell *parse)
{
	int	size;

	size = parse->outfile_size;
	if (parse->nbr_outfile > 0 && parse->tab_outfile[size])
	{
		data->output_fd = iterate_outfile_lastcmd(parse);
		if (data->output_fd < 0)
		{
			ft_printf("Error : can't open file : %s\n", parse->tab_outfile[size]->content);
			return (0);
		}
		if (dup2(data->output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (0);
		}
		return (0);
	}
	data->output_fd = STDOUT_FILENO;
	return (0);
}

int	input_file_opening_lastcmd(t_data *data, t_shell *parse, int size)
{
	data->input_fd = open(parse->tab_infile[size]->content, O_RDONLY);
	if (data->input_fd < 0)
	{
		ft_printf("minishell: %s: No such file or directory\n",
			parse->tab_infile[size - 1]->content);
		return (1);
	}
	if (dup2(data->input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}

int	check_inputfile_last_cmd(t_data *data, t_shell *parse)
{
	int	size;

	size = parse->infile_size;
	if ((parse->nbr_infile > 0 || parse->nbr_appendin > 0) && size > 0)//si HD ou INPUTFILE
	{
		while (parse->tab_infile[size]->next != NULL)
			parse->tab_infile[size] = parse->tab_infile[size]->next;
		if (data->check_hd == 1 && (parse->tab_infile[size]->type == 'A'))
		{
			if (dup2(data->hd_pipefd[data->hd_pipe_id - 1][READ],
				STDIN_FILENO) == -1)
			{
				perror("dup2");
				return (1);
			}
			return (0);
		}
		if (parse->tab_infile[size]->type == 'C')
			return (input_file_opening_lastcmd(data, parse, size));
	}
	if (dup2(data->pipefd[data->cmd_nb - 2][READ], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}
