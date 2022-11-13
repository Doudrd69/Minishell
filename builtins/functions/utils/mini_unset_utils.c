/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 13:02:44 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/12 15:27:29 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	copy_var_after_index(int i, int j, t_data *data)
{
	data->unset_env[i] = malloc(sizeof(char) * ft_strlen(data->envp[i + 1]) + 1);
	if (!data->unset_env[i])
	{
		free_tab(data->unset_env, i);
		return (0);
	}
	while (data->envp[i + 1][++j])
		data->unset_env[i][j] = data->envp[i + 1][j];
	data->unset_env[i][j] = '\0';
	return (1);
}

int	copy_var_before_index(int i, int j, t_data *data)
{
	data->unset_env[i] = malloc(sizeof(char) * ft_strlen(data->envp[i]) + 1);
	if (!data->unset_env[i])
	{
		free_tab(data->unset_env, i);
		return (0);
	}
	while (data->envp[i][++j])
		data->unset_env[i][j] = data->envp[i][j];
	data->unset_env[i][j] = '\0';
	return (1);
}

int	unset_var(int index, t_data *data, char *var_unset)
{
	int	i;

	i = 0;
	if (check_var(data->envp[index], var_unset) == 0)
	{
		if (malloc_and_cpy(data, i, index) == 1)
			return (1);
		return (0);
	}
	return (1);
}

int	malloc_and_cpy(t_data *data, int i, int index)
{
	int	j;

	data->unset_env = malloc(sizeof(char *) * (data->envp_size));//on malloc de la taille actuelle pour le NULL
	if (!data->unset_env)
		return (1);
	while (i < data->envp_size - 1)
	{
		j = -1;
		if (i >= index)
		{
			copy_var_after_index(i, j, data);
			i++;
		}
		else
		{
			copy_var_before_index(i, j, data);
			i++;
		}
	}
	data->unset_env[data->envp_size - 1] = NULL;
	return (0);
}
