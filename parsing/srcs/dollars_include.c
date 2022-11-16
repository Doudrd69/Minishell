/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_include.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:38:46 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/15 20:55:15 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	ft_next(t_shell *minishell, t_node *tmp_list, t_node **list)
{
	(*list)->prev->next = (*list)->next;
	(*list) = (*list)->next;
	(*list)->prev = (*list)->prev->prev;
	free(tmp_list->content);
	free(tmp_list);
	minishell->list_size -= 1;
}

static void	ft_prev(t_shell *minishell, t_node *new_node
		, t_node **list, t_node *tmp_list)
{
	if ((*list)->prev != NULL)
	{

		tmp_list->next = (*list)->next;
		tmp_list->prev = (*list)->prev;
		tmp_list->next->prev = new_node;
		tmp_list->prev->next = new_node;
		free((*list)->content);
		free(*list);
		(*list) = tmp_list;
	}
	else
	{
		tmp_list->next = (*list)->next;
		tmp_list->prev = NULL;
		tmp_list->next->prev = new_node;
		free((*list)->content);
		free(*list);
		(*list) = tmp_list;
		minishell->head = (*list);
	}
}

static void	replace_list(t_node **list, t_shell *minishell, t_node *tmp_list)
{
	if ((*list)->prev != NULL)
		ft_next(minishell, tmp_list, list);
	else
	{
		if ((*list)->next)
		{
			(*list) = (*list)->next;
			(*list)->prev = NULL;
		}
		else
			(*list) = NULL;
		if (tmp_list->content && tmp_list->content != minishell->cmd)
			free(tmp_list->content);
		free(tmp_list);
		minishell->head = (*list);
		minishell->list_size -= 1;
	}
}

void	include_dollar_list(t_shell *minishell, t_node **list, char *tmp)
{
	t_node	*tmp_list;
	t_node	*new_node;

	
	if (tmp)
	{
		if (ft_strlen(tmp) == 0)
		{
			free(tmp);
			tmp = NULL;
		}
	}
	if ((*list) && (*list)->next == NULL)
	{

		new_node = ft_dlstnew((void *)(tmp));
		ft_dlstadd_back(&minishell, new_node);
		tmp_list = (*list);
		replace_list(list, minishell, tmp_list);
	}
	else
	{
		new_node = ft_dlstnew((void *)(tmp));
		tmp_list = new_node;
		ft_prev(minishell, new_node, list, tmp_list);
	}
}

char	*replace_quote_dollars(t_shell *minishell, char *tmp, int j)
{
	if (minishell->mod == 2 || minishell->mod == 3)
	{
		tmp[j] = '\"';
		j++;
		tmp[j] = '\0';
	}
	else if (minishell->mod == 4)
	{
		tmp[j] = '\'';
		j++;
		tmp[j] = '\"';
		j++;
		tmp[j] = '\0';
	}
	else
	{
		tmp[j] = '\0';
	}
	return (tmp);
}
