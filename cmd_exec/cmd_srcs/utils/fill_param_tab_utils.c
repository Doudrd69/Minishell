/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param_tab_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:56:50 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/15 08:57:13 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_loop_exec(char *str, int i)
{
	if (str[i] != '-')
		return (1);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (1);
	}
	return (0);
}

t_node	*loop_to_first_arg(t_node *node, int i, int index)
{
	if (index > 0)
	{
		while (--i >= index)
			node = node->prev;
	}
	else
	{
		while (--i >= 0)
			node = node->prev;
	}
	return (node);
}
