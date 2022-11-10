/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:58:35 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/10 09:38:03 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_export(t_mini_data *data, char *var)
{
	if (check_var_exists_export(data, var))
	{
		data->new_env = new_tab_with_existing_var(data, var);
		data->p_status = 0;
		return (0);
	}
	printf("Begin export --> %d\n", data->envp_size);
	data->new_env = malloc(sizeof(char *) * (data->envp_size + 2));//1 pour la var_export et 1 pour le NULL
	if (!data->new_env)
		return (1);
	data->new_env = newtab_malloc(data, data->envp_size + 1, data->env, var);
	copy_loop(data, var, data->envp_size + 1);
	data->envp_size++;
	printf("End export --> %d\n", data->envp_size);
	data->new_env[data->envp_size] = NULL;
	data->p_status = 0;
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
				return (1);
			data->envp_size--;
			return (0);
		}
		index++;
	}
	//ft_printf("minishell: unset: '%s': not a valid identifier\n", var_unset);
	return (1);
}
