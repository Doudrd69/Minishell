/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:39:33 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 14:52:48 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	ft_prev(t_node *list_cpy, t_node *tmp, t_shell *minishell, int tab)
{
	list_cpy->next->prev = list_cpy;
	list_cpy->prev = NULL;
	(list_cpy)->type = tmp->type;
	minishell->tab_infile[tab] = list_cpy;
	free(tmp);
}

static void	ft_mid(t_node *list_cpy, t_node *tmp)
{
	list_cpy->next->prev = list_cpy;
	list_cpy->prev = tmp->prev;
	list_cpy->prev->next = list_cpy;
	(list_cpy)->type = tmp->type;
	free(tmp);
}

static void	ft_next(t_node **list_cpy, t_node *tmp, t_shell *minishell, int tab)
{
	if ((tmp)->prev != NULL)
	{
		(*list_cpy)->prev = (tmp)->prev;
		(*list_cpy)->prev->next = (*list_cpy);
		(*list_cpy)->type = tmp->type;
	}
	else
	{
		(*list_cpy)->prev = NULL;
		(*list_cpy)->type = tmp->type;
		minishell->tab_infile[tab] = *list_cpy;
	}
	free(tmp);
}

void	replace_list_quote_intab(t_node *tmp, t_node **list_cpy,
	t_shell *minishell, int i)
{
	if (tmp && tmp->prev != NULL && tmp->next->next != NULL)
	{
		ft_mid(*list_cpy, tmp);
	}
	else if (tmp && tmp->prev == NULL && tmp->next->next != NULL)
	{
		ft_prev(*list_cpy, tmp, minishell, i);
	}
	else if (tmp)
	{
		ft_next(list_cpy, tmp, minishell, i);
	}
}
