/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:06:10 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/18 08:44:10 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	value_quote_mod_1(t_shell *minishell, char *str, int i)
{
	int	check;

	check = 4;
	write_newvalue(minishell, str, check, i);
}

int	check_heredoc_dollar_mod_1(char *str, int i)
{
	int	j;
	int	tpm;

	j = i;
	if (i == 0)
		return (1);
	while (--i > 0 && str[i] == ' ')
		tpm = 0;
	while (--i > 0 && str[i] == '\'')
		tpm = 0;
	while (--i > 0 && str[i] == ' ')
		tpm = 0;
	if (i < 1)
		return (1);
	if (str[i] == '<' && str[i - 1] == '<')
		return (0);
	return (1);
}

int	check_heredoc_dollar_mod(char *str, int i)
{
	int	j;
	int	tpm;

	j = i;
	if (i == 0)
		return (1);
	while (--i > 0 && str[i] == ' ')
		tpm = 0;
	if (i < 1)
		return (1);
	if (str[i] == '<' && str[i - 1] == '<')
		return (0);
	return (1);
}

int	check_dollar_export(char *str, int i)
{
	if (i == 0 || str[i - 1] == ' ')
		return (2);
	while (i > 0 && str[i] != ' ')
		i--;
	if (i > 3)
		i--;
	else
		return (2);
	while (i > 0 && str[i] != ' ')
	{
		i--;
	}
	if (ft_strncmp(str, "export", 6) != 0)
		return (2);
	return (5);
}

int	check_dollars_mod(char *str)
{
	int	mod;
	int	i;

	i = 0;
	mod = 0;
	if (str[i + 1] != '\0' && ((str[i + 1] == 34 && str[i - 1] != 34)
			|| (str[i + 1] == 39 && str[i - 1] != 39)))
		mod = 3;
	if (str[i + 1] != '\0' && ((str[i + 1] >= 48 && str[i + 1] <= 57)
			|| str[i + 1] == 42 || str[i + 1] == 64 || str[i + 1] == 92))
	{
		mod = 1;
	}
	if (str[i + 1] != '\0' && ((str[i + 1] >= 65 && str[i + 1] <= 90)
			|| str[i + 1] == 95 || (str[i + 1] >= 97 && str[i + 1] <= 122)
			|| str[i + 1] == 32))
	{
		mod = 2;
	}
	if (str[i + 1] != '\0' && str[i + 1] == 63)
		mod = 8;
	return (mod);
}
