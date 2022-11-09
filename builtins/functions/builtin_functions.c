/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:48:10 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/09 16:26:32 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_cd(t_mini_data *data, t_node *node)
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

int	mini_pwd(t_mini_data *data, t_node *node)
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

int	mini_env(t_mini_data *data, t_node *node)
{
	int	i;

	i = 0;
	(void)node;
	if (data->pipe_check == 0)
	{
		if (data->env[0] == NULL)
		{
			data->p_status = 1;
			return (1);
		}
		while (i < data->envp_size)
		{
			printf("%s\n", data->env[i]);
			i++;
		}
		data->p_status = 0;
		return (0);
	}
	return (2);
}

int	mini_echo(t_mini_data *data, t_node *node)
{
	int	i;
	int	check;
	int	loop;

	loop = 0;
	if (no_args(node) == 0)
		return (0);
	data->echo_arg = 0;
	while (node != NULL)
	{
		i = 0;
		check = 0;
		data->str = node->content;
		node = echo_arg_newline_check(data, node, check, loop);
		if (node == NULL)
			return (0);
		loop = 1;
		if (check_if_empty(data) == 0)
			return (0);
		i = write_and_check_signs(i, data);
		if (node->next != NULL)
			write(1, " ", 1);
		node = node->next;
	}
	return (newline_arg(data));
}

int	mini_exit(t_mini_data *data, t_node *node)
{
	int	tmp;

	//cast le return en unsighned char
	tmp = ft_atoi(node->content);
	if (data->pipe_check == 0)
	{
		data->p_status = tmp;
		exit((unsigned char)tmp);
	}
	return (2);
}
