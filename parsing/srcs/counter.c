/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:34:27 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 16:25:35 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	count_ope(t_shell *minishell)
{
	int		i;
	t_node	*tmp;
	char	*str;

	tmp = minishell->head;
	minishell->quote = 0;
	minishell->dquote = 0;
	while (tmp && tmp != NULL)
	{
		i = 0;
		str = (char *)(tmp->content);
		while (str[i] != '\0')
		{
			nbr_ope(minishell, str, &i);
			i++;
		}
		tmp = tmp->next;
	}
	minishell->quote = 0;
	minishell->dquote = 0;
}

static void	count_pipe(int i, int *pipe, t_shell *minishell, char *str)
{
	if (str[i] == '\"' && minishell->dquote != 1)
		minishell->dquote = 1;
	else if (str[i] == '\"' && minishell->dquote != 0)
		minishell->dquote = 0;
	if (str[i] == '\'' && minishell->quote != 1)
		minishell->quote = 1;
	else if (str[i] == '\'' && minishell->quote != 0)
		minishell->quote = 0;
	if (str[i] == '|' && (minishell->quote == 1 || minishell->dquote == 1))
		;
	if (str[i] == '|' && minishell->quote == 0 && minishell->dquote == 0)
		(*pipe)++;
}

static void	count_redir(int *i, char *str, t_shell *minishell)
{
	if (str[*i] == '<' && str[*i + 1] != '<'
		&& minishell->quote == 0 && minishell->dquote == 0)
		minishell->nbr_infile++;
	else if (str[*i] == '<' && str[*i + 1] == '<'
		&& minishell->quote == 0 && minishell->dquote == 0)
	{
		*i += 1;
		minishell->nbr_appendin++;
		return ;
	}
	if (str[*i] == '>' && str[*i + 1] != '>'
		&& minishell->quote == 0 && minishell->dquote == 0)
		minishell->nbr_outfile++;
	else if (str[*i] == '>' && str[*i + 1] == '>'
		&& minishell->quote == 0 && minishell->dquote == 0)
	{
		*i += 1;
		minishell->nbr_appendout++;
		return ;
	}
}

void	nbr_ope(t_shell *minishell, char *str, int *i)
{
	count_pipe(*i, &minishell->nbr_pipe, minishell, str);
	count_redir(i, str, minishell);
	if (str[*i] == '$')
		minishell->nbr_dollars++;
	if (str[*i] == '\"')
		minishell->nbr_dquote++;
	if (str[*i] == '\'')
		minishell->nbr_squote++;
}
