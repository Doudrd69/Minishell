/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell_get_filling.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:51:14 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/15 10:59:07 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	test1(t_shell *minishell, char ***tab, int *k, int *x)
{
	if (minishell->strp[minishell->i] == '\'')
	{
		if (minishell->strp[minishell->i + 1] == '\0')
			(*tab)[*k][(*x)++] = minishell->strp[minishell->i];
		(minishell->i) += 1;
		while (minishell->strp[minishell->i] != '\0'
			&& minishell->strp[minishell->i] != '\'')
			(*tab)[*k][(*x)++] = minishell->strp[(minishell->i)++];
		if (minishell->strp[minishell->i] == '\''
			&& minishell->strp[minishell->i] != '\0')
			(minishell->i) += 1;
	}
}

static void	test2(t_shell *minishell, char ***tab, int *k, int *x)
{
	if (minishell->strp[minishell->i] == '\"')
	{
		if (minishell->strp[minishell->i + 1] == '\0')
		{
			(*tab)[*k][(*x)] = minishell->strp[minishell->i];
			(*x) += 1;
		}
		(minishell->i) += 1;
		while (minishell->strp[minishell->i] != '\0'
			&& minishell->strp[minishell->i] != '\"')
		{
			(*tab)[*k][(*x)] = minishell->strp[minishell->i];
			(*x) += 1;
			(minishell->i) += 1;
		}
		if (minishell->strp[minishell->i] == '\"'
			&& minishell->strp[minishell->i] != '\0')
			(minishell->i) += 1;
	}
}

static int	fill_with_quotes(t_shell *minishell, int *i, int *k, char ***tab)
{
	int	x;

	x = 0;
	while (minishell->strp[*i] != ' ' && minishell->strp[*i] != '\0')
	{
		minishell->i = (*i);
		test1(minishell, tab, k, &x);
		test2(minishell, tab, k, &x);
		(*i) = minishell->i;
		if (minishell->strp[*i] != '\0' && minishell->strp[*i] != ' '
			&& minishell->strp[*i] != '\"' && minishell->strp[*i] != '\'')
			(*tab)[*k][x++] = minishell->strp[(*i)++];
	}
	if (x != 0)
	{
		(*tab)[*k][x] = '\0';
	}
	return (x);
}

char	**ft_split_minishell_get_filling(char *str,
	char **tab, t_shell *minishell)
{
	int	i;
	int	k;
	int	x;

	i = 0;
	k = 0;
	minishell->strp = str;
	while (str[i] && str[i] != '\0')
	{
		while (str[i] == ' ' && str[i])
			i++;
		x = fill_with_quotes(minishell, &i, &k, &tab);
		if ((str[i] == ' ' || str[i - x] != '\0') && x != 0)
		{
			k++;
		}
		while (str[i] && str[i] != '\0' && str[i] == ' ')
			i++;
	}
	return (tab);
}
