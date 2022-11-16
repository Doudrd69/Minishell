/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:37:37 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/16 11:02:11 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_exec(t_data *data, t_node *n)
{
	char	**tmp;
	int		tmp_size;

	int i = 0;
	n = n->prev;
	while (n && n->next != NULL && n->next->type != 'P')
	{
		i++;
		n = n->next;
	}
	if (i == 0)
		return (display_export(data));
	while (--i > 0)
		n = n->prev;
	printf("Node before export loop ==> %s\n", n->content);
	while (n != NULL)
	{
		printf("VAR to export ==> %s\n", n->content);
		tmp_size = 0;
		tmp = data->envp;
		tmp_size = envp_size_for_tmp(tmp);
		if (mini_export(data, n->content) == 1)
			return (1);
		data->envp = data->new_env;
		if (data->check_loop_export == 1)
			free_old(tmp, tmp_size - 1);
		if (n->next == NULL)
			break ;
		data->check_loop_export = 1;
		n = n->next;
	}
	return (0);
}

int	unset_exec(t_data *data, t_node *node)
{
	char	**tmp;
	int		tmp_size;

	printf("Node before unset loop ==> %s\n", node->content);
	while (node != NULL)
	{
		printf("Var to unset ==> %s\n", node->content);
		tmp = data->envp;
		tmp_size = envp_size_for_tmp(tmp);
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

void	*node_rotation(t_node *node)
{
	if (node != NULL)
	{
		while (node && node->next->type != 'P')
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

void	exec_main(t_data *data, t_node *node, t_shell *parse,
	int (*builtins[7])(t_data *, t_node *), int g)
{
	if (data->cmd_nb > 0)
	{
		if (node && node->type == 'P')
			node = node->next;
		first_command(data, node, parse, builtins, g);
		if (data->cmd_nb > 1)
		{
			node = node_rotation(node);
			node = commands(data, node, parse, builtins, g);
			last_command(data, node, parse, builtins, g);
		}
	}
	return ;
}
