/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:48:10 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/09/19 13:26:14 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_cd(t_mini_data *data)//penser a enelver les printf
{
	printf("Before  : %s\n", getcwd(data->buff, BUF_SIZE));
	if (data->path[0] == '\0')
	{
		data->home_path = getenv("HOME");
		if (data->home_path)
		{
			chdir(data->home_path);
			printf("Current : %s\n", getcwd(data->buff, BUF_SIZE));
			*data->p_status = 0;
			return (0);
		}
		return (0);
	}
	else
	{
		if (chdir(data->path) != 0)
		{
			*data->p_status = 1;
			ft_printf("minishell: cd: %s: No such file or directory\n", data->path);
			return (1);
		}
		ft_printf("Current : %s\n", getcwd(data->buff, BUF_SIZE));
	}
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
	int		i;

	i = 0;
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
	while (i < (data->envp_size + 1))
	{
		if (i == data->envp_size - 1)
		{
			data->new_env = new_var_tab_copy(data, i, data->name, data->value);
			i++;
		}
		else
		{
			data->new_env = new_tab_copy(data, data->env, i, data->envp_size);
			i++;
		}
	}
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
	// int	pid;

	// pid = getpid();
	// return (kill(pid, 9));
	return (0);
}
