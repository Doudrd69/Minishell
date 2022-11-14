/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_space_quote_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:01:05 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 16:24:20 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	replace_list(t_node *list_cpy, t_node *tmp_list, t_node *new_node)
{
	tmp_list = new_node;
	tmp_list->next = list_cpy->next;
	tmp_list->prev = list_cpy;
	tmp_list->next->prev = new_node;
	tmp_list->prev->next = new_node;
	list_cpy->next = tmp_list;
}

void	list_nospace_quote(t_shell *minishell, t_node **list, char *tmp, int j)
{
	t_node	*tmp_list;
	t_node	*new_node;
	t_node	*list_cpy;

	tmp_list = (*list);
	while (j > 0)
	{
		tmp_list = tmp_list->next;
		j--;
	}
	if (tmp_list && tmp_list->next == NULL)
	{
		ft_dlstadd_back(&minishell, ft_dlstnew((void *)(tmp)));
		tmp_list = (*list);
	}
	else
	{
		list_cpy = tmp_list;
		new_node = ft_dlstnew((void *)(tmp));
		replace_list(list_cpy, tmp_list, new_node);
		minishell->list_size += 1;
	}
}
