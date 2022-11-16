/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:14:25 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/15 10:18:44 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_nb_of_args(t_node *node, int size)
{
	while (node->next != NULL)
	{
		if (ft_strncmp(node->content, "exit", 4) == 0)
		{
			size = 0;
			while (node->next != NULL && node->next->type != 'P')
			{
				size++;
				node = node->next;
			}
			if (size > 1)
				break ;
		}
		if (node->next != NULL)
			node = node->next;
	}
	return (size);
}
