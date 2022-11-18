/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param_tab_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:56:50 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 07:54:43 by ebrodeur         ###   ########lyon.fr   */
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

int	append_check(t_shell *p, int size)
{
	if (p->nbr_infile > 0 || p->nbr_appendin > 0)
	{
		if (p->tab_infile[size] == NULL)
			return (0);
		while (p->tab_infile[size]->next != NULL)
			p->tab_infile[size] = p->tab_infile[size]->next;
		if (p->tab_infile[size] && p->tab_infile[size]->type == 'A')
		{
			dprintf(2, "Returning Append\n");
			return (1);
		}
		if (p->tab_infile[size] && p->tab_infile[size]->type == 'C')
		{
			dprintf(2, "Returning Classic\n");
			return (2);
		}
	}
	dprintf(2, "== No INFILE for this command ==\n");
	return (0);
}
