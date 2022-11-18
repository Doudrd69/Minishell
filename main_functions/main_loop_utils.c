/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:37:37 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 13:12:44 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_exec(t_data *data, t_node *n)
{
	int		i;

	i = 0;
	n = n->prev;
	while (n && n->next != NULL && n->next->type != 'P')
	{
		i++;
		n = n->next;
	}
	if (i == 0)
		return (display_export(data, &data->envp));
	while (--i > 0)
		n = n->prev;
	if (export_loop(n, data) == 1)
		return (1);
	return (0);
}

int	unset_exec(t_data *data, t_node *node)
{
	char	**tmp;
	int		tmp_size;

	while (node != NULL)
	{
		tmp_size = 0;
		tmp = data->envp;
		tmp_size = data->envp_size;
		if (mini_unset(data, node->content) == 1)
			return (1);
		data->envp = data->unset_env;
		if (data->check_loop_export == 1)
			free_old(tmp, tmp_size);
		if (node->next == NULL)
			break ;
		data->check_loop_export = 1;
		node = node->next;
	}
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

void	*node_rotation(t_node *node, t_data *data)
{
	if (node == NULL || node->next == NULL)
		return (node);
	while (node && node->next->type != 'P')
		node = node->next;
	if (node && node->next->type == 'P')
	{
		node = node->next;
		if (node && node->next != NULL && node->next->type == 'P')
		{
			data->consecutive_pipes = 1;
			return (node);
		}
		if (node->next != NULL)
			node = node->next;
		else
			return (node);
	}
	else if (node && node->next->type == 'N')
		node = node->next->next->next;
	else
		node = node->next;
	if (node && node->type == 'P')
		node = node->next;
	return (node);
}

void	exec_main(t_data *data, t_node *node, t_shell *parse,
	int (*builtins[7])(t_data *, t_node *), int g)
{
	data->consecutive_pipes = 0;
	if (data->cmd_nb > 0)
	{
		if (node && node->type == 'P')
			node = node->next;
		first_command(data, node, parse, builtins, g);
		if (data->cmd_nb > 1)
		{
			if (node->next == NULL)
				return ;
			node = node_rotation(node, data);
			if (node->type == 'P' && node->next == NULL)
				return ;
			if (data->consecutive_pipes == 1)
				return ;
			node = commands(data, node, parse, builtins, g);
			last_command(data, node, parse, builtins, g);
		}
	}
	return ;
}
