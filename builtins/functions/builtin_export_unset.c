/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_unset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:58:35 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 15:01:41 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_export(t_data *data, char	*var)
{
	data->new_env_size = 0;
	if (check_var_exists_export(data, var))
	{
		data->envp = new_tab_with_existing_var(data, var);
		data->envp_size = data->new_size;
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
	int		index;

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

int	export_loop(t_node *n, t_data *data)
{
	int		tmp_size;
	char	**tmp;

	while (n != NULL)
	{
		tmp_size = 0;
		tmp = data->envp;
		tmp_size = data->envp_size;
		if (mini_export(data, n->content) == 1)
			return (1);
		data->envp = data->new_env;
		if (data->check_loop_export == 1)
			free_old(tmp, tmp_size);
		if (n->next == NULL)
			break ;
		data->check_loop_export = 1;
		n = n->next;
	}
	return (0);
}
