/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:39:11 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/12 19:43:37 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*minishell;

	argc += 0;
	argv += 0;
	while (1)
	{
		minishell = malloc(sizeof(t_shell));
		init_variable(minishell, 100, env);
		minishell->cmd = readline("minishell$");
		parsing(env, minishell);
		free_all(minishell);
	}
	return (0);
}

void	free_all(t_shell *minishell)
{
	t_node	*tmp;

	while (minishell->head && minishell->head != NULL)
	{
		tmp = minishell->head;
		minishell->head = minishell->head->next;
		free(tmp);
	}
	free(minishell->value);
	free(minishell->var_search);
	free(minishell);
}
