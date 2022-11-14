/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:34:31 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/12 19:34:31 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	classic_infile(char *str, int tab, t_shell *minishell,
	t_node **list)
{
	int	i;

	i = minishell->mod;
	if (i == -1)
		return (1);
	if (str[i] == '<' && str[i + 1] == '\0')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] != '<'
		&& check_quote_infile(minishell, str, strlen(str)) == 1)
	{
		minishell->infile_size = tab;
		if (search_infile(minishell, str, &(minishell->tab_infile[tab]), list) == 0)
			return (0);
	}
	return (1);
}

static int	append_infile(char *str, int tab, t_shell *minishell, t_node **list)
{
	int	i;

	i = minishell->mod;
	if (i == -1)
		return (1);
	if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '\0')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] == '<'
		&& check_quote_heredoc(minishell, str, strlen(str)) == 1)
	{
		minishell->infile_size = tab;
		if (search_heredoc(minishell, str, &(minishell->tab_infile[tab]), list) == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	classic_outfile(char *str, int tab, t_shell *minishell,
	t_node **list)
{
	int	i;

	i = minishell->mod;
	if (i == -1)
		return (1);
	if (str[i] == '>' && str[i + 1] == '\0')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] != '>'
		&& check_quote_outfile(minishell, str, strlen(str)) == 1)
	{
		minishell->outfile_size = tab;
		if (search_outfile(minishell, str, &(minishell->tab_outfile[tab]), list) == 0)
			return (0);
	}
	return (1);
}

static int	append_outfile(char *str, int tab, t_shell *minishell,
	t_node **list)
{
	int	i;

	i = minishell->mod;
	if (i == -1)
		return (1);
	if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '\0')
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] == '>'
		&& check_quote_append(minishell, str, strlen(str)) == 1)
	{
		minishell->outfile_size = tab;
		if (search_append(minishell, str, &(minishell->tab_outfile[tab]), list) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	parse_redirections(t_shell *minishell)
{
	int		size;
	t_node	*list_cpy;
	char	*str;
	int		j;

	j = 0;
	size = minishell->nbr_pipe + 1;
	init_var_redirection(minishell, size);
	list_cpy = minishell->head;
	while (list_cpy && list_cpy != NULL)
	{
		if (list_cpy->type == 'P')
			j++;
		str = (char *)(list_cpy->content);
		minishell->mod = -1;
		while (str && str[++(minishell->mod)] != '\0')
		{
			if (classic_infile(str, j, minishell, &list_cpy) == 0)
				return (0);
			if (append_infile(str, j, minishell, &list_cpy) == 0)
				return (0);
			if (classic_outfile(str, j, minishell, &list_cpy) == 0)
				return (0);
			if (append_outfile(str, j, minishell, &list_cpy) == 0)
				return (0);
			str = (char *)(list_cpy->content);
		}
		list_cpy = list_cpy->next;
	}
	return (1);
}
