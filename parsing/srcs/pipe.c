/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:42:43 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/18 16:28:20 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	ft_next(t_shell *minishell)
{
	t_node	*list_cpy;

	list_cpy = minishell->head;
	minishell->head = minishell->head->next;
	minishell->head->prev = NULL;
	minishell->list_size -= 1;
	free (list_cpy);
}

static char	*ft_tmp(char *tmp, char *str, int j, int i)
{
	char	*buff;

	(tmp) = malloc(sizeof(char) * (i + 1));
	if (tmp == NULL)
		return (NULL);
	buff = cmd_cpy((tmp), str + j, i + 1);
	buff[i] = '\0';
	return (buff);
}

int	parse_pipe(t_shell *minishell, int j, int i)
{
	t_node	*list_cpy;

	minishell->last_pipe = 0;
	minishell->pipe = minishell->nbr_pipe;
	list_cpy = minishell->head;
	while (minishell->strp[++i + j] != '\0')
	{
		if (minishell->strp[i + j] == '|' && minishell->pipe != 0
			&& check_quote_pipe(minishell,
				minishell->strp, i + j - 1) != 1)
		{
			if (check_syntax(minishell, minishell->strp, i + j) == 0)
			{
				return (0);
			}
			minishell->last_pipe = i + j + 1;
			minishell->tmpp = ft_tmp(minishell->tmpp, minishell->strp, j, i);
			if (minishell->tmpp == NULL)
				free_all_exit(minishell);
			add_last_arg(minishell, &list_cpy, &i, j);
			ft_incr_var_pipe(&j, &i);
		}
	}
	ft_next(minishell);
	return (1);
}
