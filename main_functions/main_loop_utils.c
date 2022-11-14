/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:37:37 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 19:50:49 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_exec(t_data *data, t_node *node)
{
	char	**tmp;
	int		tmp_size;

	if (node->next != NULL)
	{
		node = node->next;
		while (node != NULL)
		{
			tmp = data->envp;
			tmp_size = envp_size_for_tmp(tmp);
			if (mini_export(data, node->content) == 1)
				return (1);
			data->envp = data->new_env;
			if ((data->check_loop_export == 1 && node->next == NULL)
				|| node->next != NULL)
				free_old(tmp, tmp_size);
			if (node->next == NULL)
				break ;
			node = node->next;
		}
		return (0);
	}
	ft_printf("minishell: export: '%s': not a valid identifier\n",
		node->content);
	return (1);
}

int	unset_exec(t_data *data, t_node *node)
{
	char	**tmp;
	int		tmp_size;

	if (node->next != NULL)
		node = node->next;
	while (node != NULL)
	{
		tmp = data->envp;
		tmp_size = envp_size_for_tmp(tmp);
		if (mini_unset(data, node->content) == 1)
			return (0);
		data->envp = data->unset_env;
		if ((data->check_loop_export == 1 && node->next == NULL)
			|| node->next != NULL)
			free_old(tmp, tmp_size);
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	data->envp = data->unset_env;
	return (0);
}

int	heredoc_main(t_data *data, t_node ***intab, t_shell *parse)
{
	int		j;
	int		ptr;
	t_node	**infile_tmp;

	j = 0;
	infile_tmp = *intab;
	data->heredoc_nb = parse->nbr_appendin;
	if (data->heredoc_nb > 0)
	{
		signal(SIGINT, &signal_tmp);
		if (heredoc_exec(data, infile_tmp, parse) == 1)
			return (1);
		while (j < data->heredoc_nb)
		{
			waitpid(data->hd_pid[j], &ptr, 0);
			j++;
		}
	}
	return (0);
}

void	*node_rotation(t_node *node)
{
	if (node != NULL)
	{
		while (node->next->type != 'P')
			node = node->next;
		if (node && node->next->type == 'P')
			node = node->next->next;
		else if (node && node->next->type == 'N')
			node = node->next->next->next;
		else
			node = node->next;
		if (node && node->type == 'P')
			node = node->next;
	}
	return (node);
}

void	exec_main(t_data *data, char *envp[], t_node *node, t_shell *parse)
{
	if (data->cmd_nb > 0)
	{
		if (node && node->type == 'P')
			node = node->next;
		first_command(data->envp, data, node, parse);
		if (data->cmd_nb > 1)
		{
			node = node_rotation(node);
			node = commands(data, node, parse, envp);
			last_command(envp, data, node, parse);
		}
	}
	return ;
}
