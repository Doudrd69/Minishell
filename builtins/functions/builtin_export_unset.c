/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:58:35 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/19 11:36:51 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_export(t_mini_data *data, char *var)
{
	if (check_var_exists_export(data, var))
	{
		data->new_env = new_tab_with_existing_var(data, var);
		*data->p_status = 0;
		return (0);
	}
	data->new_env = malloc(sizeof(char *) * (data->envp_size + 1));
	if (!data->new_env)
		return (1);
	data->new_env = newtab_malloc(data, data->envp_size, data->env, var);
	copy_loop(data, var);
	data->envp_size++;
	*data->p_status = 0;
	return (0);
}

int	mini_unset(t_mini_data *data, char *var_unset)
{
	int	index;

	index = 0;
	while (index < data->envp_size)
	{
		if (ft_strnstr(data->env[index], var_unset, ft_strlen(var_unset)))
		{
			if (unset_var(index, data, var_unset) == 1)
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
