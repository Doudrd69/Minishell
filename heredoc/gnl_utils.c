/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:20:43 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/07 10:21:04 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

size_t	ft_strnlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != '\n'))
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}
