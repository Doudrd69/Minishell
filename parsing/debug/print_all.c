/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:35:35 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/17 12:32:49 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	print_dlist(t_node **list, t_node ***tab_infile, t_node ***tab_outfile, t_shell *minishell)
{
	t_node	*tmp;
	t_node	**tmp_intab;
	t_node	**tmp_outab;
	int		i;
	int		j;

	i = 1;
	tmp = (list) ? (*list) : NULL;
	while (tmp && tmp != NULL)
	{
		printf("haha\n");
		printf("list[%d] =%s*\ntype = %c\n\n", i, (char *)(tmp->content), tmp->type);
		tmp = tmp->next;
		i++;
	}
	i = 0;
	tmp_intab = (tab_infile) ? *tab_infile : NULL;
	while (tmp_intab && tmp_intab[i] && tmp_intab[i] != NULL)
	{
		j = 0;
		tmp = (tmp_intab)[i];
		while (tmp && tmp != NULL)
		{
			printf("infile_list[%d][%d] =%s, type = %c, addr = %p\n", i, j, (char *)tmp->content, (char)(tmp->type), tmp);
			j++;
			tmp = tmp->next;
		}
		i++;
	}
	i = 0;
	tmp_outab = (tab_outfile) ? *tab_outfile : NULL;
	while (tmp_outab && tmp_outab[i] && tmp_outab[i] != NULL)
	{
		j = 0;
		tmp = (tmp_outab)[i];
		while (tmp && tmp != NULL)
		{
			printf("outfile_list[%d][%d] =%s, type = %c, addr = %p\n", i, j, (char *)tmp->content, (char)(tmp->type), tmp);
			j++;
			tmp = tmp->next;
		}
		i++;
	}
	printf("list_size = %d\n\n", minishell->list_size);
}
