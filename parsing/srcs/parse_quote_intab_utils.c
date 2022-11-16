/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_intab_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:35:36 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/15 19:29:10 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	replace_listab(t_node *list_cpy, t_node *tmp_list, t_node *new_node)
{
	tmp_list = new_node;
	tmp_list->next = list_cpy->next;
	tmp_list->prev = list_cpy;
	tmp_list->next->prev = new_node;
	tmp_list->prev->next = new_node;
	list_cpy->next = tmp_list;
}

static void	list_nospace_tab(t_shell *minishell,
	t_node **list, char *tmp, int j)
{
	t_node	*tmp_list;
	t_node	*new_node;
	t_node	*list_cpy;

	tmp_list = (*list);
	minishell += 0;
	while (j > 0)
	{
		tmp_list = tmp_list->next;
		j--;
	}
	if (tmp_list && tmp_list->next == NULL)
	{
		add_back_file_list(list, ft_dlstnew(tmp));
		tmp_list = (*list);
	}
	else
	{
		list_cpy = tmp_list;
		new_node = ft_dlstnew((void *)(tmp));
		replace_listab(list_cpy, tmp_list, new_node);
	}
}

void	include_parse_quote_intab(t_shell *minishell, t_node **list_cpy, int i)
{
	char	**tab;
	char	*str;
	t_node	*tmp;

	while ((*list_cpy) && (*list_cpy) != NULL)
	{
		str = (char *)((*list_cpy)->content);
		tab = ft_split_minishell(minishell, str, ' ');
		minishell->j = -1;
		while (tab && tab[++minishell->j] != NULL)
		{
			list_nospace_tab(minishell, list_cpy,
				tab[minishell->j], minishell->j);
		}
		tmp = (*list_cpy);
		if (tmp)
			(*list_cpy) = (*list_cpy)->next;
		replace_list_quote_intab(tmp, list_cpy, minishell, i);
		while (minishell->j-- > 0 && (*list_cpy) && (*list_cpy) != NULL)
			(*list_cpy) = (*list_cpy)->next;
		free(tab);
	}
}

void	parse_quote_tab(t_shell *minishell, t_node ***tab_infile,
	t_node ***tab_outfile)
{
	t_node	**intab;
	t_node	*list_cpy;

	if ((*tab_infile) &&(*tab_infile)[0] != NULL)
	{
		minishell->tab = 0;
		intab = *tab_infile;
		
		while (intab && intab[minishell->tab] && intab[minishell->tab] != NULL)
		{
			list_cpy = (intab)[minishell->tab];
			include_parse_quote_intab(minishell, &list_cpy, minishell->tab);
			minishell->tab++;
		}
	}
	ft_parse_quote_outab(minishell, tab_outfile);
}
