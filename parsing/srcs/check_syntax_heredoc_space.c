/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_heredoc_space.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:37:18 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/16 12:49:58 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	check_syntax_begin(t_shell *minishell, char *str, int i)
{
	int	j;

	j = ft_strlen(str);
	if (j == i)
	{
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 56);
		minishell->error = 258;
		return (0);
	}
	if (j >= i + 3)
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
		{
			write(2,
				"minishell: syntax error near unexpected token `<<<'\n", 52);
			minishell->error = 258;
			return (0);
		}
	}
	return (1);
}

static int	check_syntax_mid(t_shell *minishell, char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
	{
		write(2, "minishell: syntax error near unexpected token `<<'\n", 51);
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '>' && str[i + 1] == '>')
	{
		write(2, "minishell: syntax error near unexpected token `>>'\n", 51);
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '>' && str[i + 1] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `>|'\n", 50);
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '|' && str[i + 1] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `||'\n", 51);
		minishell->error = 258;
		return (0);
	}
	return (1);
}

static int	check_syntax_end(t_shell *minishell, char *str, int i)
{
	if (str[i] == '<')
	{
		write(2, "minishell: syntax error near unexpected token `<'\n", 50);
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '>')
	{
		write(2, "minishell: syntax error near unexpected token `>'\n", 50);
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '|')
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		minishell->error = 258;
		return (0);
	}
	return (1);
}

int	check_syntax_after_heredoc(t_shell *minishell, char *str, int i)
{
	int	j;

	j = 0;
	i++;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	j = ft_strlen(str);
	if (check_syntax_begin(minishell, str, i) == 0)
		return (0);
	if (j >= i + 2)
		if (check_syntax_mid(minishell, str, i) == 0)
			return (0);
	if (j >= i + 1)
		if (check_syntax_end(minishell, str, i) == 0)
			return (0);
	return (1);
}
