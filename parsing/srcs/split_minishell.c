/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:40:46 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 20:20:20 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static char	**ft_free(int k, char **tab)
{
	while (k > 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return (NULL);
}

char	**ft_split_minishell(t_shell *minishell, char *str, char c)
{
	char	**tab;
	int		nbrw;

	if (!str)
		return (NULL);
	nbrw = ft_nbr_words_split_minishell(minishell, str, c);
	printf("NBRW===%d\n", nbrw);
	if (nbrw == 0)
	{
		if (strlen(str) == 2)
		{
			printf("minishell: : command not found\n");
			minishell->error = 127;
		}
		return (NULL);
	}
	tab = (char **)malloc(sizeof(char *) * (nbrw + 1));
	if (tab == NULL)
		return (NULL);
	tab[nbrw] = 0;
	if (ft_split_minishell_malloc_ws(str, c, tab))
		return (ft_free(ft_split_minishell_malloc_ws(str, c, tab), tab));
	tab = ft_split_minishell_get_filling(str, tab, minishell);
	return (tab);
}
