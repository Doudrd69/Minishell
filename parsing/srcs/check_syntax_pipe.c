/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:43:39 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 18:43:39 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static char	*ft_prev(char *tmp, char *str, int j, int i)
{
	tmp = malloc(sizeof(char) * (ft_strlen(str) - (j + i - 1)));
	tmp = cmd_cpy(tmp, str + j + i, ft_strlen(str) - (j + i - 1));
	(tmp)[ft_strlen(str) - (j + i)] = '\0';
	return (tmp);
}

static void	ft_add_pipe(t_shell *minishell, char *tmp
	, int *i, t_node **list_cpy)
{
	ft_dlstadd_back((&(minishell)), ft_dlstnew((void *)tmp));
	*list_cpy = (*list_cpy)->next;
	ft_dlstadd_back((&(minishell)), ft_dlstnew((void *)"|\0"));
	*list_cpy = (*list_cpy)->next;
	(*list_cpy)->type = 'P';
	(*i)++;
}

void	add_last_arg(t_shell *minishell, t_node **list_cpy, int *i, int j)
{
	ft_add_pipe(minishell, minishell->tmpp, i, list_cpy);
	if (minishell->pipe == 0 && minishell->strp[(*i) + j] != '\0')
	{
		minishell->tmpp = ft_prev(minishell->tmpp, minishell->strp, j, (*i));
		ft_dlstadd_back((&(minishell)), ft_dlstnew((void *)minishell->tmpp));
	}
}

static int	check_syntax_utils(t_shell *minishell, int j, int i, char *str)
{
	while (--j >= 0 && str[j] == ' ')
	{
		if (j == 0)
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			minishell->error = 258;
			return (0);
		}
	}
	while (str[++i] != '\0' && (str[i] == ' ' || str[i] == '|'))
	{
		if (str[i] == '|')
		{
			if (str[i + 1] == '|')
				printf("minishell: syntax error near unexpected token `||'\n");
			else
				printf("minishell: syntax error near unexpected token `|'\n");
			minishell->error = 258;
			return (0);
		}
	}
	return (1);
}

int	check_syntax(t_shell *minishell, char *str, int i)
{
	int	j;

	j = i;
	if (i == 0 || str[i + 1] == '\0')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		minishell->error = 258;
		return (0);
	}
	if (str[i + 1] == '|')
	{
		printf("minishell: syntax error near unexpected token `||'\n");
		minishell->error = 258;
		return (0);
	}
	if (check_syntax_utils(minishell, j, i, str) == 0)
		return (0);
	return (1);
}
