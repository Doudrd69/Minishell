/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:40:10 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 20:43:37 by wmonacho         ###   ########lyon.fr   */
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
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] != '<'
		&& check_quote_infile(minishell, str, strlen(str)) == 1)
	{
		minishell->infile_size = tab;
		if (search_infile(minishell, str, &(minishell->tab_infile[tab]),
				list) == 0)
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
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '<' && str[i + 1] != '\0' && str[i + 1] == '<'
		&& check_quote_heredoc(minishell, str, strlen(str)) == 1)
	{
		minishell->infile_size = tab;
		if (search_heredoc(minishell, str, &(minishell->tab_infile[tab]),
				list) == 0)
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
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] != '>'
		&& check_quote_outfile(minishell, str, strlen(str)) == 1)
	{
		minishell->outfile_size = tab;
		if (search_outfile(minishell, str, &(minishell->tab_outfile[tab]),
				list) == 0)
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
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i] == '>' && str[i + 1] != '\0' && str[i + 1] == '>'
		&& check_quote_append(minishell, str, strlen(str)) == 1)
	{
		minishell->outfile_size = tab;
		if (search_append(minishell, str, &(minishell->tab_outfile[tab]),
				list) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	sorting_loop(t_shell *minishell, char *str, t_node **list_cpy, int j)
{
	while (str && str[++(minishell->mod)] != '\0')
	{
		if (classic_infile(str, j, minishell, list_cpy) == 0)
			return (0);
		if (append_infile(str, j, minishell, list_cpy) == 0)
			return (0);
		if (classic_outfile(str, j, minishell, list_cpy) == 0)
			return (0);
		if (append_outfile(str, j, minishell, list_cpy) == 0)
			return (0);
		str = (char *)((*list_cpy)->content);
	}
	return (1);
}
