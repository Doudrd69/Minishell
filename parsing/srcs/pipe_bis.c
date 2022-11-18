/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_bis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:42:57 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/18 17:17:37 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

char	*cmd_cpy(char *dest, char *src, int size)
{
	int	i;

	if (size == 0)
		return (NULL);
	i = -1;
	dest[1] = src[1];
	while (src[++i] && i < size - 1)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

static void	check_quote_utils(t_shell *minishell, char *str, int i)
{
	if ((str[i]) == '\"' && minishell->dquote != 1)
		minishell->dquote = 1;
	else if (str[i] == '\"' && minishell->dquote != 0)
		minishell->dquote = 0;
	if (str[i] == '\'' && minishell->quote != 1)
		minishell->quote = 1;
	else if (str[i] == '\'' && minishell->quote != 0)
		minishell->quote = 0;
}

int	check_quote_pipe(t_shell *minishell, char *str, int pipe)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = str;
	pipe = pipe - minishell->last_pipe;
	str = str + minishell->last_pipe;
	minishell->dquote = 0;
	minishell->quote = 0;
	while (str[i] != '\0')
	{
		check_quote_utils(minishell, str, i);
		if (str[i] == '|' && i == pipe
			&& (minishell->dquote == 1 || minishell->quote == 1))
			return (1);
		if (str[i] == '|' && i == pipe
			&& minishell->dquote == 0 && minishell->quote == 0)
		{
			minishell->pipe--;
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_incr_var_pipe(int *j, int *i)
{
	*(j) += (*(i));
	*(i) = 0;
}
