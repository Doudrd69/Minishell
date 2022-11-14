/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:48:10 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 07:30:20 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_cd(t_data *data, t_node *node)
{
	data->oldpwd = getcwd(data->buff_oldpwd, BUF_SIZE);
	if (node->next == NULL && ft_strncmp(node->content, "cd", 2) == 0)
	{
		if (no_path(data) == 1)
			return (1);
	}
	else
	{
		if (path_exists(data, node) == 1)
			return (1);
	}
	if (update_pwd(data) == 1)
		return (1);
	if (update_old_pwd(data) == 1)
		return (1);
	return (0);
}

int	mini_pwd(t_data *data, t_node *node)
{
	(void)node;
	if (data->pipe_check == 0)
	{
		if (getcwd(data->buff, BUF_SIZE) == NULL)
		{
			data->p_status = 1;
			return (1);
		}
		ft_printf("%s\n", data->buff);
		data->p_status = 0;
		return (0);
	}
	return (2);
}

int	mini_env(t_data *data, t_node *node)
{
	int	i;
	int	j;

	i = -1;
	(void)node;
	if (data->pipe_check == 0)
	{
		if (data->envp[0] == NULL)
			return (1);
		while (++i < data->envp_size)
		{
			j = 0;
			while (data->envp[i][j])
			{
				if (data->envp[i][j] == '=')
				{
					ft_printf("%s\n", data->envp[i]);
					break ;
				}
				j++;
			}
		}
		return (0);
	}
	return (2);
}

int	mini_echo(t_data *data, t_node *node)
{
	int	check;
	int	loop;

	loop = 0;
	data->echo_arg = 0;
	if (no_args(node) == 0)
		return (0);
	if (data->pipe_check == 0 && data->outfile_check == 0)
	{
		while (node != NULL && node->type != 'P')
		{
			check = 0;
			data->str = node->content;
			node = echo_arg_newline_check(data, node, check, loop);
			if (node == NULL)
				return (0);
			loop = 1;
			write_and_check_signs(0, data);
			if (node->next != NULL && node->next->type != 'P')
				write(1, " ", 1);
			node = node->next;
		}
		return (newline_arg(data));
	}
	return (2);
}

int	mini_exit(t_data *data, t_node *node)
{
	int	tmp;

	tmp = ft_atoi(node->content);
	if (data->pipe_check == 0)
	{
		data->p_status = tmp;
		exit((unsigned char)tmp);
	}
	return (2);
}
