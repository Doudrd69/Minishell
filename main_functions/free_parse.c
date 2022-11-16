/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:03:29 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/16 08:45:29 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../parsing/parsing.h"

void	free_outab(t_shell *minishell)
{
	int		i;
	t_node	**tmp_outab;
	t_node	*node;
	t_node	*tmp;

	i = 0;
	tmp_outab = minishell->tab_outfile;
	while (tmp_outab && tmp_outab[i])
	{
		tmp = (tmp_outab)[i];
		while (tmp && tmp != NULL)
		{
			node = tmp->next;
			test_free((void *)(tmp->content));
			test_free((void *)(tmp));
			tmp = node;
		}
		i++;
	}
	test_free((void *)(minishell->tab_outfile));
}

void	free_tab_parse(t_shell *minishell)
{
	t_node	**tmp_intab;
	t_node	*tmp;
	t_node	*node;
	int		i;

	i = 0;
	tmp_intab = minishell->tab_infile;
	while (tmp_intab && tmp_intab[i])
	{
		tmp = (tmp_intab)[i];
		while (tmp && tmp != NULL)
		{
			node = tmp->next;
			test_free((void *)(tmp->content));
			test_free((void *)(tmp));
			tmp = node;
		}
		i++;
	}
	test_free((void *)(minishell->tab_infile));
	free_outab(minishell);
}

void	free_all(t_shell *minishell)
{
	t_node	*tmp;

	dprintf(2, "fin|%p\n", minishell->head);
	while (minishell->head && minishell->head != NULL)
	{
		tmp = minishell->head;
		minishell->head = minishell->head->next;
		printf("free:=%p=, =%p=, =%s=\n", tmp->content, tmp, tmp->content);
		test_free((void *)(tmp->content));
		test_free((void *)(tmp));
	}
	free_tab_parse(minishell);
	test_free((void *)(minishell->value));
	test_free((void *)(minishell->var_search));
	test_free((void *)(minishell->home_path));
	free(minishell);
}
