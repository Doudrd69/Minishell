/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:29 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 16:47:25 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	parse_space(t_shell *minishell)
{
	t_node	*list_cpy;
	t_node	*tmp;
	char	*str;
	char	**tab;
	int		j;

	list_cpy = minishell->head;
	while (list_cpy && list_cpy != NULL)
	{
		str = (char *)(list_cpy->content);
		tab = ft_split(str, ' ');
		if (tab == NULL)
		{
			minishell->head = NULL;
			list_cpy = minishell->head;
		}
		j = -1;
		while (tab && tab[++j] != NULL)
			list_nospace(minishell, &list_cpy, tab[j], j);
		tmp = list_cpy;
		last_verif(tmp, list_cpy, minishell, j);
	}
}

void	list_nospace(t_shell *minishell, t_node **list, char *tmp, int j)
{
	t_node	*tmp_list;
	t_node	*new_node;
	t_node	*list_cpy;

	list_cpy = NULL;
	new_node = NULL;
	minishell->tmp_lnospace = tmp;
	tmp_list = (*list);
	while (j > 0)
	{
		tmp_list = tmp_list->next;
		j--;
	}
	if (tmp_list && tmp_list->next == NULL)
	{
		ft_dlstadd_back(&minishell,
			ft_dlstnew((void *)(minishell->tmp_lnospace)));
		tmp_list = (*list);
	}
	else
		list_no_space_else(minishell, list_cpy, tmp_list, new_node);
}
