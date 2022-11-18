/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:14:50 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 07:18:15 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	first_command(t_data *data, t_node *node, t_shell *parse,
	int (*builtins[5])(t_data *, t_node *), int g)
{
	signal(SIGQUIT, &sigtest);
	signal(SIGINT, &sigint_handler_in_process);
	data->first_cmd_pid = fork_creation(data->first_cmd_pid);
	if (data->first_cmd_pid == 0)
	{
		dprintf(2, "(begin) First ==> %s\n", node->content);
		if (check_inputfile(data, parse) != 0)
		{
			dprintf(2, "debug exit errno\n");
			exit(errno);
		}
		dprintf(2, "debug 1\n");
		if (node != NULL)
		{
			data->env.tab1 = get_path(data->envp, data, data->env.tab1);
			data->env.param_tab1 = fill_param_tab(node, data,
					data->env.param_tab1);
			while (data->env.param_tab1[data->size_ptab1])
				data->size_ptab1++;
		}
		dprintf(2, "debug 2\n");
		if (check_outfile(data, parse) != 0)
			exit(errno);
		first_cmd_execution(data, node, builtins, g);
	}
}

void	last_command(t_data *data, t_node *node, t_shell *parse,
	int (*builtins[5])(t_data *, t_node *), int g)
{
	signal(SIGQUIT, &sigtest);
	signal(SIGINT, &sigint_handler_in_process);
	data->last_cmd_pid = fork_creation(data->last_cmd_pid);
	if (data->last_cmd_pid == 0)
	{
		if (check_inputfile_last_cmd(data, parse) != 0)
			exit(errno);
		if (check_outfile_last_cmd(data, parse) != 0)
			exit(errno);
		data->env.tab2 = get_path(data->envp, data, data->env.tab2);
		data->env.param_tab2 = fill_param_tab(node, data, data->env.param_tab2);
		while (data->env.param_tab2[data->size_ptab2])
			data->size_ptab2++;
		last_cmd_execution(data, node, builtins, g);
	}
}

void	*commands(t_data *data, t_node *node, t_shell *parse,
	int (*builtins[5])(t_data *, t_node *), int g)
{
	int	i;
	int	*pid;

	i = -1;
	data->pipe_id = 1;
	pid = malloc(sizeof(int) * (data->cmd_nb - 2));
	if (!pid)
		return (0);
	while (++i < (data->cmd_nb - 2))
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			ft_printf("Error while creating processes\n");
			return (0);
		}
		if (pid[i] == 0)
			command_exec(data, node, parse, builtins, g);
		node = node_rotation(node, data);
		data->pipe_id++;
	}
	free(pid);
	return (node);
}
