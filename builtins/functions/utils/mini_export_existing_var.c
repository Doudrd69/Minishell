/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_existing_var.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:26:30 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 13:47:35 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_var_exists_export(t_data *data, char *var_export)
{
	int		i;
	char	*str;

	i = 0;
	str = get_var_name(var_export);
	while (i < data->envp_size)
	{
		if (ft_strnstr(data->envp[i], str, ft_strlen(str)))
		{
			if (check_var(data->envp[i], str) == 0)
			{
				data->var_position = i;
				free(str);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	malloc_new_env(t_data *data, int i)
{
	data->new_env[i] = malloc(sizeof(char) * ft_strlen(data->envp[i]) + 1);
	if (!data->new_env[i])
	{
		free_tab(data->new_env, data->envp_size);
		return (1);
	}
	return (0);
}

char	**malloc_tab_with_existing_var(t_data *data, char *var)
{
	int	i;

	i = 0;
	while (i < data->envp_size)
	{
		if (i == data->var_position)
		{
			data->new_env[i] = malloc(sizeof(char) * (ft_strlen(var) + 2));
			if (!data->new_env[i])
			{
				free_tab(data->new_env, data->envp_size);
				return (0);
			}
		}
		else
		{
			if (malloc_new_env(data, i) == 1)
				return (NULL);
		}
		i++;
	}
	return (data->new_env);
}

char	**copy_value(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->envp[i][j])
	{
		data->new_env[i][j] = data->envp[i][j];
		j++;
	}
	data->new_env[i][j] = '\0';
	return (data->new_env);
}

char	**new_tab_with_existing_var(t_data *data, char *var)
{
	int	i;

	i = 0;
	data->new_env = malloc(sizeof(char *) * data->envp_size);
	if (!data->new_env)
	{
		free_tab(data->new_env, data->envp_size);
		return (0);
	}
	data->new_env = malloc_tab_with_existing_var(data, var);
	while (i < data->envp_size)
	{
		if (i == data->var_position)
			ft_strlcpy(data->new_env[i], var, ft_strlen(var), 1);
		else
			data->new_env = copy_value(data, i);
		i++;
	}
	return (data->new_env);
}
