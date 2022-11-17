/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_command_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:28:28 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/17 14:05:44 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	iterate_outfile_lastcmd(t_shell *parse)
{
	int	size;

	size = parse->outfile_size;
	while (parse->tab_outfile[size] != NULL)
	{
		if (parse->tab_outfile[size]->next == NULL)
		{
			if (parse->tab_outfile[size]->type == 'C')
				return (open(parse->tab_outfile[size]->content, O_WRONLY
						| O_TRUNC | O_CREAT, 0666));
			else
				return (open(parse->tab_outfile[size]->content, O_WRONLY
						| O_APPEND | O_CREAT, 0666));
		}
		if (parse->tab_outfile[size]->type == 'C')
			open(parse->tab_outfile[size]->content, O_WRONLY | O_TRUNC
				| O_CREAT, 0666);
		else
			open(parse->tab_outfile[size]->content, O_WRONLY | O_APPEND
				| O_CREAT, 0666);
		parse->tab_outfile[size] = parse->tab_outfile[size]->next;
	}
	return (-1);
}

int	check_outfile_last_cmd(t_data *data, t_shell *parse)
{
	int	size;

	size = parse->outfile_size;
	if ((parse->nbr_outfile > 0 || parse->nbr_appendout > 0)
		&& parse->tab_outfile[size])
	{
		data->output_fd = iterate_outfile_lastcmd(parse);
		if (data->output_fd < 0)
		{
			ft_printf("minishell: %s: %s\n", parse->tab_outfile[size]->content,
				strerror(errno));
			return (1);
		}
		if (dup2(data->output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
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
		ft_printf("minishell: %s: %s\n", parse->tab_infile[size]->content,
			strerror(errno));
		return (1);
	}
	if (dup2(data->input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}

int	dup_to_pipe(t_data *data)
{
	if (dup2(data->pipefd[data->cmd_nb - 2][READ], STDIN_FILENO) == -1)
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
	if ((parse->nbr_infile > 0 || parse->nbr_appendin > 0) && size > 0)
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
	return (dup_to_pipe(data));
}
