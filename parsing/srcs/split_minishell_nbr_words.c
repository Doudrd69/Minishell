/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_minishell_nbr_words.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:00 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/17 16:53:04 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	last_conditions(char const *str, int *wlen, int *i)
{
	if (str[*i] == '\"')
	{
		(*i) += 1;
		while (str[*i] != '\0' && str[*i] != '\"')
		{
			(*i) += 1;
			(*wlen) += 1;
		}
		if (str[*i] == '\"' && str[*i] != '\0')
			(*i) += 1;
	}
	if (str[*i] != '\0' && str[*i] != ' '
		&& str[*i] != '\"' && str[*i] != '\'')
	{
		(*i) += 1;
		(*wlen) += 1;
	}
	return ;
}

static void	count_lenght_ws(char const *str, int *wlen, int *i)
{
	while (str[*i] != ' ' && str[*i])
	{
		if (str[*i] == '\'')
		{
			(*i) += 1;
			while (str[*i] != '\0' && str[*i] != '\'')
			{
				(*i) += 1;
				(*wlen) += 1;
			}
			if (str[*i] == '\'' && str[*i] != '\0')
				(*i) += 1;
		}
		last_conditions(str, wlen, i);
	}
}

int	ft_nbr_words_split_minishell(char const	*str, char charset)
{
	int	i;
	int	wlen;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		wlen = 0;
		while (str[i] && str[i] == ' ')
			i++;
		count_lenght_ws(str, &wlen, &i);
		if ((str[i] == charset || str[i] == '\0') && wlen != 0)
			j++;
		while (str[i] == charset && str[i])
			i++;
	}
	return (j);
}
