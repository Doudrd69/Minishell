/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell_nbr_words.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:00 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/17 15:45:59 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	last_loop(char const *str, char charset, int *i)
{
	while (str[*i] != charset && str[*i] && str[*i] != '\0')
	{
		if (str[*i] == '\'')
		{
			(*i) += 1;
			return (1);
		}
		if (str[*i] == '\"')
		{
			(*i) += 1;
			return (2);
		}
		if (str[*i] != '\0')
			(*i) += 1;
	}
	return (0);
}

static int	count_word(char const *str, char charset, int *i, int *nbrw)
{
	while (str[*i] == charset && str[*i] && str[*i] != '\0')
	{
		(*i) += 1;
	}
	if (str[*i] != charset && str[*i] && str[*i] != '\0')
	{
		(*nbrw) += 1;
		if (str[*i] == '\"' && (str[*i + 1] == '\"' || str[*i + 1] == '\0'))
			(*nbrw) -= 1;
		if (str[*i] == '\'' && (str[*i + 1] == '\'' || str[*i + 1] == '\0'))
			(*nbrw) -= 1;
	}
	return (last_loop(str, charset, i));
}

static int	pass_quote(t_shell *minishell, char const *str, char charset, int *i)
{
	minishell->mod = 0;
	if (str[*i] != '\0' && str[(*i) + 1] == '\0')
		return (0);
	while (str[*i] != '\0' && str[*i] != '\'')
		(*i) += 1;
	if (str[*i] != '\0')
	{
		while (str[*i] != '\0' && str[*i] != charset)
		{
			if (str[*i] == '\'' && str[(*i)] != '\0')
			{
				(*i) += 1;
				break ;
			}
			(*i) += 1;
		}
	}
	return (1);
}

static int	pass_dquote(t_shell *minishell, char const *str, char charset, int *i)
{
	int	j;

	j = 0;
	minishell->mod = 0;
	// if (str[*i + 1] == '\"')
	// {
	// 	(*i) += 1;
	// 	return (1);
	// }
	if (str[*i] != '\0' && str[(*i) + 1] == '\0')
		return (0);
	while (str[*i] != '\0' && str[*i] != '\"')
		(*i) += 1;
	if (str[*i] != '\0')
	{
		if (str[*i] == '\"')
		{
			(*i) += 1;
		}
		while (str[*i] != '\0' && str[*i] != charset && str[*i] != '\"')
			(*i) += 1;
		printf("str=====%s\n", str + *i);
	}
	return (1);
}

int	ft_nbr_words_split_minishell(t_shell *minishell,
	char const	*str, char charset)
{
	int	nbrw;
	int	i;

	nbrw = 0;
	i = 0;
	while (str[i] && str[i] != '\0')
	{
		minishell->mod = count_word(str, charset, &i, &nbrw);
		if (minishell->mod == 1)
		{
			while ((str[i] && str[i] == '\'')
				|| (str[i] && minishell->mod == 1))
				if (pass_quote(minishell, str, charset, &i) == 0)
					return (nbrw);
		}
		if (minishell->mod == 2)
		{
			while ((str[i] && str[i] == '"') || (str[i] && minishell->mod == 2))
			{
				if (pass_dquote(minishell, str, charset, &i) == 0)
					return (nbrw);
				printf("endwhile=%s=\n", str + i);
			}
		}
		printf("st!!!!!!=%s=\n", str + i);
	}
	return (nbrw);
}
