/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_getenv_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:05:14 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 07:12:25 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*check_and_return_var(t_data *data, char **envp, char *var, int i)
{
	int	j;
	int	k;

	j = -1;
	k = 0;
	if (check_var(envp[i], var) == 0)
	{
		data->home_path = malloc(sizeof(char) * ft_strlen(envp[i]) + 1);
		if (!data->home_path)
			return (NULL);
		while (envp[i][++j])
		{
			data->home_path[k] = envp[i][j];
			k++;
		}
		data->home_path[k] = '\0';
		return (data->home_path);
	}
	return (NULL);
}
