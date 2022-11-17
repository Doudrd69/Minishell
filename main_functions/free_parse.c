/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:03:29 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/17 17:03:03 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../parsing/parsing.h"

int	test_free(void *tmp)
{
	if (tmp == NULL)
		return (0);
	else
	{
		free(tmp);
		tmp = NULL;
	}
	return (1);
}

void	free_outab(t_shell *minishell)
{
	int		i;
	t_node	**tmp_outab;
	t_node	*node;
	t_node	*tmp;

	i = 0;
	tmp_outab = minishell->tab_outfile;
	while (tmp_outab && i <= minishell->outfile_size)
	{
		printf("free tab\n");
		tmp = (tmp_outab)[i];
		while (tmp && tmp != NULL)
		{
			node = tmp->next;
			if (tmp->content != minishell->cmd)
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
	while (tmp_intab && i <= minishell->infile_size)
	{
		tmp = (tmp_intab)[i];
		while (tmp && tmp != NULL)
		{
			node = tmp->next;
			if (tmp->content != minishell->cmd)
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

	while (minishell->head && minishell->head != NULL)
	{
		tmp = minishell->head;
		minishell->head = minishell->head->next;
		if (tmp->content != minishell->cmd)
			test_free((void *)(tmp->content));
		test_free((void *)(tmp));
	}
	free_tab_parse(minishell);
	test_free((void *)(minishell->value));
	test_free((void *)(minishell->var_search));
	test_free((void *)(minishell->home_path));
	free(minishell);
}
