/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:26:28 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/16 17:50:52 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	free_old(char **tab, int size)
{
	int	i;

	i = size - 1;
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
}

void	free_unset_tab(t_data *data)
{
	if (data->unset_env && data->unset_env_check == 1)
	{
		free_tab(data->unset_env, data->unset_env_size);
		data->unset_env_check = 0;
	}
	return ;
}

int	envp_size_for_tmp(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("TMP [%d] ==> %s\n", i, tab[i]);
		i++;
	}
	return (i);
}
