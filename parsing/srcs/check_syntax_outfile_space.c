/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_outfile_space.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:33:52 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/12 20:33:12 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	check_syntax_begin(t_shell *minishell, char *str, int i)
{
	int	j;

	j = ft_strlen(str);
	if (j == i)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->error = 258;
		return (0);
	}
	if (j >= i + 3)
	{
		if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
		{
			printf("minishell: syntax error near unexpected token `<<<'\n");
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
		printf("minishell: syntax error near unexpected token `<<'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '>' && str[i + 1] == '>')
	{
		printf("minishell: syntax error near unexpected token `>>'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '>' && str[i + 1] == '|')
	{
		printf("minishell: syntax error near unexpected token `>|'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '|' && str[i + 1] == '|')
	{
		printf("minishell: syntax error near unexpected token `||'\n");
		minishell->error = 258;
		return (0);
	}
	return (1);
}

static int	check_syntax_end(t_shell *minishell, char *str, int i)
{
	if (str[i] == '<')
	{
		printf("minishell: syntax error near unexpected token `<'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '>')
	{
		printf("minishell: syntax error near unexpected token `>'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		minishell->error = 258;
		return (0);
	}
	return (1);
}

int	check_syntax_after_outfile(t_shell *minishell, char *str, int i)
{
	int	j;

	j = 0;
	minishell += 0;
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
