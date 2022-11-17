/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exit_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:14:25 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/17 17:01:26 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_arg_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_nb_of_args(t_node *node, int size)
{
	if (check_arg_exit(node->content) == 1)
	{
		if (node->next == NULL && ft_strncmp(node->content, "exit", 4) == 0)
			return (0);
		return (-1);
	}
	size = 0;
	while (node != NULL)
	{
		if (node != NULL && node->type != 'P')
			size++;
		if (size > 1)
			break ;
		node = node->next;
	}
	return (size);
}
