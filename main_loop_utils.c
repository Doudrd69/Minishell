/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:37:37 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/02 17:09:08 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "cmd_exec/cmd_include/pipex_bonus.h"

int	export_exec(t_mini_data *mini_data, t_data *data, t_node *node)
{
	if (node->next != NULL)
	{
		node = node->next;
		while (node != NULL)
		{
			mini_export(mini_data, node->content);
			if (node->next == NULL)
				break ;
			mini_data->env = mini_data->new_env;
			data->envp = mini_data->new_env;
			node = node->next;
		}
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
	ft_printf("minishell: export: '%s': not a valid identifier\n", node->content);
	return (1);
}

int	unset_exec(t_mini_data *mini_data, t_data *data, t_node *node)
{
	if (node->next != NULL)
		node = node->next;
	while (node != NULL)
	{
		if (mini_unset(mini_data, node->content) == 1)
			return (1);
		if (node->next == NULL)
			break ;
		mini_data->env = mini_data->unset_env;
		data->envp = mini_data->unset_env;
		node = node->next;
	}
	mini_data->unset_env_check = 1;
	if (mini_data->new_env && mini_data->new_env_check == 1)
	{
		free_tab(mini_data->new_env, mini_data->envp_size);
		mini_data->new_env_check = 0;
	}
	mini_data->env = mini_data->unset_env;
	data->envp = mini_data->unset_env;
	return (0);
}

void	heredoc_main(t_data *data, t_shell *parse)
{
	int	j;
	int	ptr;

	j = 0;
	data->heredoc_nb = parse->nbr_appendin;
	if (data->heredoc_nb > 0)
	{
		heredoc_exec(data, parse);
		while (j < data->heredoc_nb)
		{
			waitpid(data->hd_pid[j], &ptr, 0);
			j++;
		}
	}
	return ;
}

void	*node_rotation(t_node *node)
{
	if (node->next->type == 'P')
		node = node->next->next;
	else if (node->next->type == 'N')
		node = node->next->next->next;
	else
		node = node->next;
	if (node->type == 'P')
		node = node->next;
	return (node);
}

void	exec_main(t_data *data, char *envp[], t_node *node, t_shell *parse)
{
	if (data->cmd_nb > 0)
	{
		if (node->type == 'P')
			node = node->next;
		first_command(envp, data, node, parse);//passer les infile/outfile ici
		if (data->cmd_nb > 1)
		{
			node = node_rotation(node);
			node = commands(data, node, parse, envp);
			last_command(envp, data, node, parse);
		}
	}
	return ;
}
