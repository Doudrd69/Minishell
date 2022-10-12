/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:48:10 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/07 10:10:21 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_cd(t_mini_data *data)//penser a enelver les printf
{
	data->oldpwd = getcwd(data->buff_oldpwd, BUF_SIZE);
	if (data->path[0] == '\0')
	{
		if (no_path(data) == 1)
			return (1);
	}
	else
	{
		if (path_exists(data) == 1)
			return (1);
	}
	if (update_pwd(data) == 1)
		return (1);
	if (update_old_pwd(data) == 1)
		return (1);
	return (0);
}

int	mini_pwd(t_mini_data *data)
{
	if (getcwd(data->buff, BUF_SIZE) == NULL)
	{
		*data->p_status = 1;
		return (1);
	}
	ft_printf("%s\n", data->buff);
	*data->p_status = 0;
	return (0);
}

int	mini_env(t_mini_data *data)
{
	int	i;

	i = 0;
	if (data->env[0] == NULL)//bash semble renvoyer 0 dans ce cas
	{
		*data->p_status= 1;
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

int	mini_echo(t_mini_data *data)//a modifier pour ecrire dans le bon FD (si redirection) 
{
	int	i;

	i = 0;
	if (!data->str || (data->str[0] == '$' && data->str[1] == '\0'))
	{
		write(1, "\n", 1);
		*data->p_status = 0;
		return (0);
	}
	i = write_and_check_signs(i, data);
	if (data->str[i] == '$' && data->str[i + 1] == '\0')
		write(1, &data->str[i], 1);
	if (data->echo_arg == 0)
		write(1, "\n", 1);
	*data->p_status = 0;
	return (0);
}

int	mini_export(t_mini_data *data)
{
	if (check_var_exists_export(data))
	{
		data->new_env = new_tab_with_existing_var(data);
		*data->p_status = 0;
		return (0);
	}
	data->new_env = malloc(sizeof(char *) * (data->envp_size + 1));
	if (!data->new_env)
		return (1);
	data->new_env = new_tab_malloc(data, data->envp_size, data->env, data->name, data->value);
	copy_loop(data);
	data->envp_size++;
	*data->p_status = 0;
	return (0);
}

int	mini_unset(t_mini_data *data)
{
	int	index;

	index = 0;
	while (index < data->envp_size)
	{
		if (ft_strnstr(data->env[index], data->var_name, ft_strlen(data->var_name)))
		{
			if (unset_var(index, data) == 1)
			{
				*data->p_status = 1;
				return (1);
			}
			return (0);
		}
		index++;
	}
	return (1);
}

int	mini_exit()
{
	return (0);
}
