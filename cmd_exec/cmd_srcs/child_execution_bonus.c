/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_execution_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:45:19 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 14:17:07 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(char **tab, char **param, t_data *data)
{
	int	i;

	i = -1;
	if (tab == NULL)
	{
		write(2, "PATH not found : can't execute command : ", 41);
		write(2, param[0], ft_strlen(param[0]));
		write(2, "\n", 1);
		exit(1);
	}
	while (tab[++i])
	{
		if (access(tab[i], X_OK) == 0)
		{
			if (execve(tab[i], param, data->envp) == -1)
			{
				perror("execve");
				exit(errno);
			}
		}
	}
	if (ft_strncmp(param[0], "exit", 4) == 0)
		exit(3);
	exit_cmd_not_found(param);
}

void	first_cmd_execution(t_data *data, t_node *node,
	int (*builtins[7])(t_data *, t_node *), int g)
{
	if (access(data->env.param_tab1[0], X_OK) == 0)
		exec_cmd_path(data, data->envp);
	else
	{
		if (data->env.tab1 != NULL)
			data->env.tab1 = join_arg(data->env.param_tab1, data->env.tab1);
		if (data->exec.pipe_check == 1)
			close_pipe(data, (data->cmd_nb - 2));
		if (data->heredoc_nb > 0)
			close_hd_pipe(data, data->heredoc_nb - 1);
		check_file(data->env.param_tab1[0]);
		if (builtins_loop(data->builtins_name, builtins, node, data, &g) == 0)
			free_and_exit_builtin(data->env.tab1, data->env.param_tab1,
				data->size_ptab1 - 1);
		exec_cmd(data->env.tab1, data->env.param_tab1, data);
	}
}

void	last_cmd_execution(t_data *data, t_node *node,
	int (*builtins[7])(t_data *, t_node *), int g)
{
	if (access(data->env.param_tab2[0], X_OK) == 0)
		exec_cmd_path_last(data);
	else
	{
		if (data->env.tab2 != NULL)
			data->env.tab2 = join_arg(data->env.param_tab2, data->env.tab2);
		if (data->exec.pipe_check == 1)
			close_pipe(data, (data->cmd_nb - 2));
		if (data->heredoc_nb > 0)
			close_hd_pipe(data, data->heredoc_nb - 1);
		check_file(data->env.param_tab2[0]);
		if (builtins_loop(data->builtins_name, builtins, node, data, &g) == 0)
			free_and_exit_builtin(data->env.tab2, data->env.param_tab2,
				data->size_ptab2 - 1);
		exec_cmd(data->env.tab2, data->env.param_tab2, data);
	}
}

void	cmd_execution(t_data *data, int pipe_id, t_node *node,
	int (*builtins[7])(t_data *, t_node *), int g)
{
	if (access(data->env.param_tab3[0], X_OK) == 0)
		cmd_exec_path(data, pipe_id);
	else
	{
		if (data->env.tab3 != NULL)
			data->env.tab3 = join_arg(data->env.param_tab3, data->env.tab3);
		if (pipe_id != (data->cmd_nb - 2))
			close_pipe(data, pipe_id + 1);
		else
			close_pipe(data, pipe_id);
		if (data->input_fd > 0)
			close(data->input_fd);
		if (data->heredoc_nb > 0)
			close_hd_pipe(data, data->heredoc_nb - 1);
		check_file(data->env.param_tab3[0]);
		if (builtins_loop(data->builtins_name, builtins, node, data, &g) == 0)
			free_and_exit_builtin(data->env.tab3, data->env.param_tab3,
				data->size_ptab3 - 1);
		exec_cmd(data->env.tab3, data->env.param_tab3, data);
	}
}
