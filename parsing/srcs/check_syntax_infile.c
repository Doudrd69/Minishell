/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_infile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:34:13 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/12 19:34:13 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	check_syntax_begin(t_shell *minishell, char *str, int i)
{
	if (str[i + 1] == '|' && str[i + 2] == '|')
	{
		printf("minishell: syntax error near unexpected token `||'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i + 1] == '>' && str[i + 2] == '>' && str[i + 3] == '>')
	{
		printf("minishell: syntax error near unexpected token `>>'\n");
		minishell->error = 258;
		return (0);
	}
	else if (str[i + 1] == '>' && str[i + 2] == '>')
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		minishell->error = 258;
		return (0);
	}
	return (1);
}

int	check_syntax_infile(t_shell *minishell, char *str, int i)
{
	int	j;

	j = ft_strlen(str);
	if (j == i)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->error = 258;
		return (0);
	}
	if (j >= i + 2)
		if (check_syntax_begin(minishell, str, i) == 0)
			return (0);
	if (j >= i + 1)
	{
		if (str[i + 1] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			minishell->error = 258;
			return (0);
		}
	}
	if (check_syntax_after_infile(minishell, str, i) == 0)
		return (0);
	return (1);
}
