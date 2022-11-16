/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_redir_malloc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:55:14 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/16 15:23:16 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	search_outfile_malloc(t_shell *minishell,
	char *str, char **tmp, char **cpy)
{
	(*tmp) = malloc(sizeof(char) * (minishell->file_search + 2));
	if (!(*tmp))
		free_all_exit(minishell);
	(*cpy) = malloc(sizeof(char) * ((ft_strlen(str)
					- (minishell->file_search) + 1)));
	if (!(*cpy))
	{
		free(tmp);
		free_all_exit(minishell);
	}
}

void	search_return_exit(t_shell *minishell, char *cpy, char **tmp)
{
	if (!cpy)
	{
		free((*tmp));
		return (free_all_exit(minishell));
	}
}

int	tab_null_parse_quote(t_shell *minishell, t_node **list_cpy, char **tab)
{
	if (tab == NULL)
	{
		unstack_list(minishell, list_cpy);
		return (0);
	}
	return (1);
}

void	return_malloc_change_var(t_shell *minishell, char *tmp, char *cpy)
{
	if (!tmp)
	{
		free(cpy);
		return (free_all_exit(minishell));
	}
}
