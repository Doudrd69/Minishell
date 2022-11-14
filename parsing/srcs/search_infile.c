/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_infile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:41:59 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 17:16:32 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	include_infile_list(t_node **tab_list, char *tmp)
{
	t_node	*list_cpy;

	list_cpy = *tab_list;
	add_back_file_list(tab_list, ft_dlstnew(tmp));
	list_cpy = *tab_list;
	while (list_cpy && list_cpy->next != NULL && list_cpy != NULL)
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
	printf("str + j==%s\n", str + i);
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
	if (j == 0)
		cpy = NULL;
	printf("cpy==%s\n", cpy);
	include_dollar_list(minishell, list, cpy);
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
	cpy = malloc(sizeof(char) * ((ft_strlen(str) - (file) + 1)));
	tmp = cmd_cpy(tmp, str + (minishell->mod) + 1 + space, file + 1);
	include_infile_list(tab_infile, tmp);
	delete_file_list(minishell, list, cpy, str);
	minishell->mod = -1;
	return (1);
}
