/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_oldpwd_update.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:15:16 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/12 15:25:01 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*oldpwd_copy(t_data *data, char *str, int size)
{
	ft_strlcpy(str, "OLDPWD=", 7, 0);
	ft_strlcpy(&str[7], data->oldpwd, size, 1);
	return (str);
}

int	check_length(t_data *data, size_t size, int position, char *str)
{
	if (size > ft_strlen(data->envp[position]))
	{
		data->envp[position] = str;
		return (0);
	}
	return (1);
}
