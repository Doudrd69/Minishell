/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sapce_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:42:10 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 16:47:30 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	ft_prev(t_node *list_cpy, t_shell *minishell, t_node *tmp)
{
	list_cpy->next->prev = list_cpy;
	list_cpy->prev = NULL;
	minishell->head = list_cpy;
	free(tmp);
	minishell->list_size -= 1;
}

static void	ft_mid(t_node *list_cpy, t_node *tmp, t_shell *minishell)
{
	list_cpy->next->prev = list_cpy;
	list_cpy->prev = tmp->prev;
	list_cpy->prev->next = list_cpy;
	free(tmp);
	minishell->list_size -= 1;
}

static void	ft_next(t_node *list_cpy, t_shell *minishell, t_node *tmp)
{
	if (tmp->prev != NULL)
	{
		list_cpy->prev = tmp->prev;
		list_cpy->prev->next = list_cpy;
	}
	else
	{
		list_cpy->prev = NULL;
		minishell->head = list_cpy;
	}
	free(tmp);
	minishell->list_size -= 1;
}

void	list_no_space_else(t_shell *minishell, t_node *list_cpy,
	t_node *tmp_list, t_node *new_node)
{
	list_cpy = tmp_list;
	new_node = ft_dlstnew((void *)(minishell->tmp_lnospace));
	tmp_list = new_node;
	tmp_list->next = list_cpy->next;
	tmp_list->prev = list_cpy;
	tmp_list->next->prev = new_node;
	tmp_list->prev->next = new_node;
	list_cpy->next = tmp_list;
	minishell->list_size += 1;
	return ;
}

void	last_verif(t_node *tmp, t_node *list_cpy, t_shell *minishell, int j)
{
	if (tmp)
		list_cpy = list_cpy->next;
	if (tmp && tmp->prev != NULL && tmp->next->next != NULL)
		ft_mid(list_cpy, tmp, minishell);
	else if (tmp && tmp->prev == NULL && tmp->next->next != NULL)
		ft_prev(list_cpy, minishell, tmp);
	else if (tmp)
		ft_next(list_cpy, minishell, tmp);
	while (j-- >= 0 && list_cpy && list_cpy != NULL)
		list_cpy = list_cpy->next;
}
