/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:37:37 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/21 14:13:16 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "cmd_exec/cmd_include/pipex_bonus.h"

int	export_exec(t_mini_data *mini_data, t_data *data, t_node *node)
{
	if (node->next != NULL)
		node = node->next;
	mini_export(mini_data, node->content);
	mini_data->new_env_check = 1;
	if (mini_data->unset_env && mini_data->unset_env_check == 1)
	{
		free_tab(mini_data->unset_env, mini_data->envp_size - 2);
		mini_data->unset_env_check = 0;
	}
	mini_data->env = mini_data->new_env;
	data->envp = mini_data->new_env;
	return (0);
}

int	unset_exec(t_mini_data *mini_data, t_data *data, t_node *node)
{
	if (node->next != NULL)
		node = node->next;
	mini_unset(mini_data, node->content);
	mini_data->unset_env_check = 1;
	if (mini_data->new_env)
	{
		free_tab(mini_data->new_env, mini_data->envp_size);
		mini_data->new_env_check = 0;
	}
	mini_data->env = mini_data->unset_env;
	data->envp = mini_data->unset_env;
	return (0);
}

void	heredoc_main(t_data *data)
{
	int	j;
	int	ptr;

	j = 0;
	if (data->heredoc_nb > 0)
	{
		heredoc_exec(data);
		while (j < data->heredoc_nb)
		{
			waitpid(data->hd_pid[j], &ptr, 0);
			j++;
		}
	}
	return ;
}

void	exec_main(t_data *data, char *envp[], t_node *node)
{
	if (data->cmd_nb > 0)
	{
		first_command(envp, data, node);
		if (data->cmd_nb > 1)
		{
			commands(data, envp);
			last_command(envp, data);
		}
	}
	return ;
}
