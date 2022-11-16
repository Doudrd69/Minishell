/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:39:16 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/15 18:29:20 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	init_variable(t_shell *minishell, int env_size, char **envp)
{
	minishell->cmd = NULL;
	minishell->env_search = envp;
	minishell->env_size = env_size;
	minishell->home_path = NULL;
	minishell->quote = 0;
	minishell->dquote = 0;
	minishell->error = 0;
	minishell->nbr_pipe = 0;
	minishell->nbr_infile = 0;
	minishell->nbr_outfile = 0;
	minishell->nbr_appendin = 0;
	minishell->nbr_appendout = 0;
	minishell->nbr_dollars = 0;
	minishell->nbr_dquote = 0;
	minishell->nbr_squote = 0;
	minishell->envp = envp;
	minishell->value = NULL;
	minishell->var_search = NULL;
	init_dlist_var(minishell);
}

void	init_dlist_var(t_shell *minishell)
{
	minishell->tmpp = NULL;
	minishell->strp = NULL;
	minishell->head = NULL;
	minishell->tab_infile = NULL;
	minishell->tab_outfile = NULL;
	minishell->tail = NULL;
	minishell->list_size = 0;
}

void	init_var_redirection(t_shell *minishell, int size)
{
	int	i;

	i = 0;
	// minishell->tab_infile = (t_node **)malloc(sizeof(t_node *) * (size + 1));
	// // minishell->tab_outfile = (t_node **)malloc(sizeof(t_node *) * (size + 1));
	// while (i <= size)
	// {
	// 	minishell->tab_infile[i] = NULL;
	// 	minishell->tab_outfile[i] = NULL;
	// 	i++;
	// }
	(void) size;
	minishell->infile_size = 0;
	minishell->outfile_size = 0;
}
