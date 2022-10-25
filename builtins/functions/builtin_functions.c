/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:48:10 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/25 14:00:30 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_cd(t_mini_data *data, t_node *node)
{
	data->oldpwd = getcwd(data->buff_oldpwd, BUF_SIZE);
	if (node->content == NULL)
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
	if (getcwd(data->buff, BUF_SIZE) == NULL)
	{
		*data->p_status = 1;
		return (1);
	}
	ft_printf("%s\n", data->buff);
	*data->p_status = 0;
	return (0);
}

int	mini_env(t_mini_data *data, t_node *node)
{
	(void)node;
	int	i;

	i = 0;
	if (data->env[0] == NULL)
	{
		*data->p_status = 1;
		return (1);
	}
	while (i < data->envp_size)
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	*data->p_status = 0;
	return (0);
}

int	mini_echo(t_mini_data *data, t_node *node)
{
	int	i;

	while (node != NULL)
	{
		i = 0;
		data->str = node->content;
		if (!data->str || (data->str[0] == '$' && data->str[1] == '\0'))
		{
			write(1, "\n", 1);
			*data->p_status = 0;
			return (0);
		}
		i = write_and_check_signs(i, data);
		if (data->str[i] == '$' && data->str[i + 1] == '\0')
			write(1, &data->str[i], 1);
		write(1, " ", 1);
		node = node->next;
	}
	if (data->echo_arg == 0)
		write(1, "\n", 1);
	*data->p_status = 0;
	return (0);
}

int	mini_exit()
{
	printf("PID when call exit : %d\n", getpid());
	// *data->p_status = 2;
	// exit (*data->p_status);
	exit(0);
}
