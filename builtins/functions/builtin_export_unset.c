/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:58:35 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 10:22:27 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_export(t_data *data, char *var)
{
	data->new_env_size = 0;
	if (check_var_exists_export(data, var))
	{
		data->new_env = new_tab_with_existing_var(data, var);
		data->p_status = 0;
		return (0);
	}
	data->new_env = malloc(sizeof(char *) * (data->envp_size + 2));
	if (!data->new_env)
		return (1);
	data->new_env = newtab_malloc(data, data->envp_size + 1, data->envp, var);
	copy_loop(data, var, data->envp_size + 1);
	data->envp_size++;
	data->new_env[data->envp_size] = NULL;
	while (data->new_env[data->new_env_size])
		data->new_env_size++;
	data->p_status = 0;
	return (0);
}

int	mini_unset(t_data *data, char *var_unset)
{
	int	index;

	index = 0;
	data->unset_env_size = 0;
	while (index < data->envp_size)
	{
		if (ft_strnstr(data->envp[index], var_unset,
				ft_strlen(var_unset)) && index < data->envp_size)
		{
			if (unset_var(index, data, var_unset) == 1)
				return (1);
			while (data->unset_env[data->unset_env_size])
				data->unset_env_size++;
			data->envp_size--;
			return (0);
		}
		index++;
	}
	return (1);
}
