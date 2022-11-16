/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:59 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/16 14:46:38 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	include_infile_list(t_node **tab_list, char *tmp)
{
	t_node	*list_cpy;

	add_back_file_list(tab_list, ft_dlstnew(tmp));
	list_cpy = *tab_list;
	while (list_cpy->next != NULL)
				list_cpy = list_cpy->next;
	list_cpy->type = 'C';
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
	i++;
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	i = dl_fl_search_infile(str, i);
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
		print_dlist(&minishell->head, NULL, NULL, minishell);
		return ;
	}
	include_dollar_list(minishell, list, cpy);
}

int	if_only_space(char *str)
{
	int	j;
	int	i;

	i = 0;
	j = ft_strlen(str);
	while (str[i] != '\0' && str[i] == ' ')
		i++;
	if (i == j)
		return (1);
	return (0);
}

int	check_quote_infile(t_shell *minishell, char *str, int len)
{
	int	i;
	int	dquote;

	i = 0;
	dquote = 0;
	minishell->quote = 0;
	while (i < len + 1 && str[i] != '\0')
	{
		if (str[i] == '\"' && minishell->quote != 1)
			minishell->quote = 1;
		else if (str[i] == '\"' && minishell->quote != 0)
			minishell->quote = 0;
		if (str[i] == '\'' && dquote != 1)
			dquote = 1;
		else if (str[i] == '\'' && dquote != 0)
			dquote = 0;
		if (str[i] == '<' && str[i + 1] != '<'
			&& (minishell->quote == 1 || dquote == 1))
			return (0);
		if (str[i] == '<' && str[i + 1] != '<'
			&& (minishell->quote == 0 || dquote == 0))
			return (1);
		i++;
	}
	return (1);
}

int	search_infile(t_shell *minishell, char *str, t_node **tab_infile,
	t_node **list)
{
	int		i;
	int		file;
	char	*tmp;
	char	*cpy;
	int		space;

	file = 0;
	i = minishell->mod;
	space = 0;
	if (check_syntax_infile(minishell, str, i) == 0)
		return (0);
	while (str[++i] != '\0' && str[i] == ' ')
		space++;
	file = main_loop_search_infile(str, i, file);
	tmp = malloc(sizeof(char) * (file + 2));
	if (!tmp)
		free_all_exit(minishell);
	cpy = malloc(sizeof(char) * ((ft_strlen(str) - (file) + 1)));
	if (!cpy)
		free_all_exit(minishell);
	tmp = cmd_cpy(tmp, str + (minishell->mod) + 1 + space, file + 1);
	include_infile_list(tab_infile, tmp);
	delete_file_list(minishell, list, cpy, str);
	minishell->mod = -1;
	return (1);
}
