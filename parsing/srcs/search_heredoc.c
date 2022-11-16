/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:42:05 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/16 15:12:02 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	include_heredoc_list(t_node **tab_list, char *tmp)
{
	t_node	*list_cpy;

	list_cpy = *tab_list;
	add_back_file_list(tab_list, ft_dlstnew(tmp));
	list_cpy = *tab_list;
	while (list_cpy && list_cpy->next != NULL && list_cpy != NULL)
				list_cpy = list_cpy->next;
	list_cpy->type = 'A';
}

static void	delete_file_list(t_shell *minishell, t_node **list,
	char *cpy, char *str)
{
	int	i;
	int	j;

	i = minishell->mod;
	j = -1;
	while (++j < i)
		cpy[j] = str[j];
	i += 2;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	i = dl_fl_search_heredoc(str, i);
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	while (str[i] != '\0')
		cpy[j++] = str[i++];
	cpy[j] = '\0';
	if (j == 0 || if_only_space(cpy) == 1)
	{
		free(cpy);
		cpy = NULL;
		unstack_list(minishell, list);
		return ;
	}
	include_dollar_list(minishell, list, cpy);
}

int	check_quote_heredoc(t_shell *minishell, char *str, int len)
{
	int	i;
	int	dquote;

	i = 0;
	dquote = 0;
	minishell->quote = 0;
	while (i < len + 1 && str[i] != '\0')
	{
		if (str[i] == '\"' && minishell->quote != 1 && str[i - 1] != '\\')
			minishell->quote = 1;
		else if (str[i] == '\"' && minishell->quote != 0 && str[i - 1] != '\\')
			minishell->quote = 0;
		if (str[i] == '\'' && dquote != 1 && str[i - 1] != '\\')
			dquote = 1;
		else if (str[i] == '\'' && dquote != 0 && str[i - 1] != '\\')
			dquote = 0;
		if (str[i] == '<' && str[i + 1] == '<'
			&& (minishell->quote == 1 || dquote == 1))
			return (0);
		if (str[i] == '<' && str[i + 1] == '<'
			&& (minishell->quote == 0 || dquote == 0))
			return (1);
		i++;
	}
	return (1);
}

int	search_heredoc(t_shell *minishell, char *str, t_node **tab_infile,
	t_node **list)
{
	int		i;
	int		file;
	char	*tmp;
	char	*cpy;
	int		space;

	file = 0;
	i = minishell->mod;
	i += 1;
	space = 0;
	if (check_syntax_heredoc(minishell, str, i) == 0)
		return (0);
	while (str[++i] != '\0' && str[i] == ' ')
		space++;
	file = main_loop_search_heredoc(str, i, file);
	tmp = malloc(sizeof(char) * (file + 2));
	if (!tmp)
		free_all_exit(minishell);
	cpy = malloc(sizeof(char) * ((ft_strlen(str) - (file) + 1)));
	search_return_exit(minishell, cpy, &tmp);
	tmp = cmd_cpy(tmp, str + (minishell->mod + 1) + 1 + space, file + 1);
	include_heredoc_list(tab_infile, tmp);
	delete_file_list(minishell, list, cpy, str);
	minishell->mod = -1;
	return (1);
}
