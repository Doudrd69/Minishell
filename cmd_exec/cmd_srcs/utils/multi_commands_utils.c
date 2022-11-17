/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:44:21 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/17 20:04:44 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	iterate_outfile_cmd(t_data *data, t_shell *parse)
{
	int	index;

	index = data->pipe_id;
	while (parse->tab_outfile[index] != NULL)
	{
		if (parse->tab_outfile[index]->next == NULL)
		{
			if (parse->tab_outfile[index]->type == 'C')
				return (open(parse->tab_outfile[index]->content,
						O_WRONLY | O_TRUNC | O_CREAT, 0666));
			else
				return (open(parse->tab_outfile[index]->content,
						O_WRONLY | O_APPEND | O_CREAT, 0666));
		}
		if (parse->tab_outfile[index]->type == 'C')
			open(parse->tab_outfile[index]->content, O_WRONLY
				| O_TRUNC | O_CREAT, 0666);
		else
			open(parse->tab_outfile[index]->content, O_WRONLY
				| O_APPEND | O_CREAT, 0666);
		parse->tab_outfile[index] = parse->tab_outfile[index]->next;
	}
	return (-1);
}

int	check_outfile_cmd(t_data *data, t_shell *parse)
{
	if ((parse->nbr_outfile > 0 || parse->nbr_outfile > 0)
		&& parse->tab_outfile[data->pipe_id])
	{
		data->output_fd = iterate_outfile_cmd(data, parse);
		if (data->output_fd < 0)
		{
			ft_printf("minishell: %s: %s\n",
				parse->tab_outfile[data->pipe_id]->content, strerror(errno));
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
		ft_printf("minishell: %s: %s\n",
			parse->tab_infile[data->pipe_id]->content, strerror(errno));
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
	int	index;
	int	check;

	index = data->pipe_id;
	check = append_check(parse, index);
	if (check != 0)
	{
		if (check == 1)
		{
			if (dup2(data->hd_pipefd[data->hd_pipe_id - 2][READ],
				STDIN_FILENO) == -1)
			{
				perror("dup2");
				return (1);
			}
			return (0);
		}
		if (check == 2)
			return (input_file_opening_cmd(data, parse));
	}
	return (multi_cmd_dup_to_pipe(data, index));
}

void	command_exec(t_data *data, t_node *node, t_shell *parse,
	int (*builtins[5])(t_data *, t_node *), int g)
{
	signal(SIGQUIT, &sigtest);
	signal(SIGINT, &sigint_handler_in_process);
	if (check_inputfile_cmd(data, parse) != 0)
		exit(errno);
	if (check_outfile_cmd(data, parse) != 0)
		exit(errno);
	data->env.tab3 = get_path(data->envp, data, data->env.tab3);
	data->env.param_tab3 = fill_param_tab(node, data, data->env.param_tab3);
	while (data->env.param_tab3[data->size_ptab3])
		data->size_ptab3++;
	cmd_execution(data, data->pipe_id, node, builtins, g);
}
