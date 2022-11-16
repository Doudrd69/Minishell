/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:39:48 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/16 10:58:19 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"
#include "../../includes/minishell.h"

static void	ft_prev(t_node *list_cpy, t_shell *minishell, t_node *tmp)
{
	list_cpy->next->prev = list_cpy;
	list_cpy->prev = NULL;
	minishell->head = list_cpy;
	list_cpy->type = tmp->type;
	if (tmp->content && tmp->content != minishell->cmd)
		free(tmp->content);
	free(tmp);
	minishell->list_size -= 1;
}

static void	ft_mid(t_node *list_cpy, t_node *tmp, t_shell *minishell)
{
	list_cpy->next->prev = list_cpy;
	list_cpy->prev = tmp->prev;
	list_cpy->prev->next = list_cpy;
	list_cpy->type = tmp->type;
	if (tmp->content)
		free(tmp->content);
	free(tmp);
	minishell->list_size -= 1;
}

static void	ft_next(t_node *list_cpy, t_shell *minishell, t_node *tmp)
{
	if (tmp->prev != NULL)
	{
		list_cpy->prev = tmp->prev;
		list_cpy->prev->next = list_cpy;
		list_cpy->type = tmp->type;
	}
	else
	{
		list_cpy->prev = NULL;
		minishell->head = list_cpy;
		minishell->head->type = tmp->type;
	}
	if (tmp->content && tmp->content != minishell->cmd)
		free(tmp->content);
	free(tmp);
	minishell->list_size -= 1;
}

static void	include_parse_quote(t_node **list_cpy, t_shell *minishell, int j)
{
	char	**tab;
	char	*str;
	t_node	*tmp;

	str = (char *)((*list_cpy)->content);
	tab = ft_split_minishell(minishell, str, ' ');
	if (tab == NULL)
	{
		unstack_list(minishell, list_cpy);
		return ;
		// free((minishell->head));
		// minishell->head = NULL;
		// (*list_cpy) = minishell->head;
	}
	j = -1;
	while (tab && tab[++j] != NULL)
		list_nospace(minishell, list_cpy, tab[j], j);
	tmp = (*list_cpy);
	if (tmp)
		(*list_cpy) = (*list_cpy)->next;
	if (tmp && tmp->prev != NULL && tmp->next->next != NULL)
		ft_mid((*list_cpy), tmp, minishell);
	else if (tmp && tmp->prev == NULL && tmp->next->next != NULL)
		ft_prev((*list_cpy), minishell, tmp);
	else if (tmp)
		ft_next((*list_cpy), minishell, tmp);
	while (j-- >= 0 && (*list_cpy) && (*list_cpy) != NULL)
		(*list_cpy) = (*list_cpy)->next;
	free(tab);
}

void	parse_space_quote(t_shell *minishell)
{
	t_node	*list_cpy;
	int		j;

	list_cpy = minishell->head;
	j = -1;
	while (list_cpy && list_cpy != NULL)
	{
		include_parse_quote(&list_cpy, minishell, j);
		dprintf(2, "bb|%p, %p\n", minishell->head, list_cpy);
	}
}
