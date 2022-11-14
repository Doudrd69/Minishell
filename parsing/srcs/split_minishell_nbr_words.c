/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell_nbr_words.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:00 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/12 19:41:00 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	count_word(char const *str, char charset, int *i, int *nbrw)
{
	while (str[*i] == charset && str[*i] && str[*i] != '\0')
	{
		(*i) += 1;
	}
	if (str[*i] != charset && str[*i] && str[*i] != '\0')
	{
		(*nbrw) += 1;
		if (str[*i] == '\"' && str[*i + 1] == '\"')
			(*nbrw) -= 1;
		if (str[*i] == '\'' && str[*i + 1] == '\'')
			(*nbrw) -= 1;
	}
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

static int	pass_quote(char const *str, char charset, int *i)
{
	if (str[*i] != '\0' && str[(*i) + 1] == '\0')
		return (0);
	while (str[*i] != '\0' && str[*i] != '\'')
		(*i) += 1;
	if (str[*i] != '\0')
	{
		while (str[*i] != '\0' && str[*i] != charset)
			(*i) += 1;
	}
	return (1);
}

static int	pass_dquote(char const *str, char charset, int *i)
{
	int	j;

	j = 0;
	if (str[*i] == '\"')
	{
		(*i) += 1;
		return (1);
	}
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
			if (pass_quote(str, charset, &i) == 0)
				return (nbrw);
		if (minishell->mod == 2)
			if (pass_dquote(str, charset, &i) == 0)
				return (nbrw);
	}
	return (nbrw);
}
