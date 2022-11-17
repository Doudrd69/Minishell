/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote_dollars.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:36:54 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/17 19:47:45 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	check_dquote_dollars(char *str, int *dquote, int i, int *quote)
{
	if (str[i] == '\"' && *dquote != 1)
		*dquote = 1;
	else if (str[i] == '\"' && *dquote != 0)
		*dquote = 0;
	if (str[i] == '\'' && *quote != 1)
		*quote = 1;
	else if (str[i] == '\'' && *quote != 0)
		*quote = 0;
}

int	check_quote_in_quote_dollars(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"')
		{
			while (str[++i] != '\0' && str[i] != '\"')
			{
				if (str[i] == '\'' && str[i + 1] == '$' && str[i + 2] == '\'')
					return (5);
			}
			return (4);
		}
		if (str[i] == '\'')
			break ;
	}
	return (1);
}

static int	check_quote_dollars_bis(char *str, int i, int dquote, int quote)
{
	if (i == 0)
		return (-1);
	if (str[i] == '$' && str[i - 1] == '"'
		&& str[i + 1] == '"' && quote != 1)
		return (6);
	if (str[i] == '$' && str[i - 1] == '\''
		&& str[i + 1] == '\'' && dquote != 1)
		return (7);
	return (0);
}

static void	check_mod(t_shell *minishell, int i, int dquote, int quote)
{
	if (minishell->strp[i] == '$' && minishell->strp[i + 1] == '"'
		&& dquote == 1 && quote != 1)
		minishell->mod = 8;
	else if (i > 0 && minishell->strp[i] == '$' && minishell->strp[i - 1] == '"'
		&& dquote == 1 && quote != 1)
		minishell->mod = 2;
	else if (minishell->strp[i] == '$' && dquote == 1 && quote != 1)
		minishell->mod = 3;
	else if (minishell->strp[i] == '$' && quote == 1 && dquote != 1)
		minishell->mod = 1;
	else if (minishell->strp[i] == '$' && dquote != 1 && quote != 1)
		minishell->mod = 0;
}

int	check_quote_dollars(t_shell *minishell, char *str, int max)
{
	int	i;
	int	quote;
	int	dquote;
	int	j;

	i = -1;
	quote = 0;
	minishell->strp = str;
	minishell->mod = -1;
	dquote = 0;
	j = 0;
	while (++i <= max)
	{
		check_dquote_dollars(str, &dquote, i, &quote);
		j = check_quote_dollars_bis(str, i, dquote, quote);
		if (j == 6 || j == 7)
			minishell->mod = j;
		else
			check_mod(minishell, i, dquote, quote);
	}
	if (minishell->mod != -1)
		return (minishell->mod);
	return (check_quote_in_quote_dollars(str));
}
