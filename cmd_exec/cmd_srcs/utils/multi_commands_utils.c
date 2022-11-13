/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:49:50 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/12 20:05:41 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


int	iterate_outfile_cmd(t_data *data, t_shell *parse)
{
	while (parse->tab_outfile[data->pipe_id] != NULL)
	{
		if (parse->tab_outfile[data->pipe_id]->next == NULL)
		{
			if (parse->tab_outfile[data->pipe_id]->type == 'C')
				return (open(parse->tab_outfile[data->pipe_id]->content, O_WRONLY
					| O_TRUNC | O_CREAT, 0666));
			else
				return (open(parse->tab_outfile[data->pipe_id]->content,
					O_WRONLY | O_APPEND | O_CREAT, 0666));
		}
		if (parse->tab_outfile[data->pipe_id]->type == 'C')
			open(parse->tab_outfile[data->pipe_id]->content, O_WRONLY |
				O_TRUNC | O_CREAT, 0666);
		else
			open(parse->tab_outfile[data->pipe_id]->content, O_WRONLY |
				O_APPEND | O_CREAT, 0666);
		parse->tab_outfile[data->pipe_id] = parse->tab_outfile[data->pipe_id]->next;
	}
	return (-1);
}

int	check_outfile_cmd(t_data *data, t_shell *parse)
{
	if ((parse->nbr_outfile > 0 || parse->nbr_outfile > 0) && parse->tab_outfile[data->pipe_id])
	{
		data->output_fd = iterate_outfile_cmd(data, parse);
		if (data->output_fd < 0)
		{
			ft_printf("minishell: %s: %s\n", parse->tab_outfile[data->pipe_id]->content, strerror(errno));
			return (0);
		}
		if (dup2(data->output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (0);
		}
		return (0);
	}
	if (dup2(data->pipefd[data->pipe_id][WRITE], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}

int	input_file_opening_cmd(t_data *data, t_shell *parse)
{
	data->input_fd = open(parse->tab_infile[data->pipe_id]->content, O_RDONLY);
	if (data->input_fd < 0)
	{
		ft_printf("minishell: %s: %s\n", parse->tab_infile[data->pipe_id]->content, strerror(errno));
		return (1);
	}
	if (dup2(data->input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}

int	check_inputfile_cmd(t_data *data, t_shell *parse)
{
	if ((parse->nbr_infile > 0 || parse->nbr_appendin > 0) && parse->infile_size > 0)
	{
		while (parse->tab_infile[data->pipe_id]->next != NULL)
			parse->tab_infile[data->pipe_id] = parse->tab_infile[data->pipe_id]->next;
		if (data->check_hd == 1 && (parse->tab_infile[data->pipe_id]->type == 'A'))
		{
			if (dup2(data->hd_pipefd[data->hd_pipe_id - 2][READ],
				STDIN_FILENO) == -1)
			{
				perror("dup2");
				return (1);
			}
			return (0);
		}
		if (parse->tab_infile[data->pipe_id]->type == 'C')
			return (input_file_opening_cmd(data, parse));
	}
	if (dup2(data->pipefd[data->pipe_id - 1][READ], STDIN_FILENO) == -1)
	{
		perror("dup2 TEST 2");
		return (1);
	}
	return (0);
}


void	command_exec(t_data *data, t_node *node, t_shell *parse, char *envp[])
{
	signal(SIGQUIT, &sigtest);
	signal(SIGINT, &sigint_handler_in_process);
	if (check_inputfile_cmd(data, parse) != 0)
		exit(errno);
	if (check_outfile_cmd(data, parse) != 0)
		exit(errno);
	data->env.tab3 = get_path(envp, data, data->env.tab3);
	data->env.param_tab3 = fill_param_tab(node, data, data->env.param_tab3);
	while (data->env.param_tab3[data->size_ptab3])
		data->size_ptab3++;
	cmd_execution(data, envp, data->pipe_id);
}
