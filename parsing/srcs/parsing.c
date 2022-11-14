/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:40:16 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/12 19:45:08 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	check_arg(int ac)
{
	if (ac < 2)
		return (0);
	return (1);
}

void	parsing(char **env, t_shell *minishell)
{
	minishell->envp = env;
	first_parse(minishell, minishell->cmd);
	count_ope(minishell);
	tokenizers_arg(minishell);
}

int	tokenizers_arg(t_shell *minishell)
{
	if (minishell->nbr_pipe > 0)
	{
		if (parse_pipe(minishell, 0, -1) == 0)
			return (0);
	}
	print_dlist(&minishell->head, &minishell->tab_infile,
		&minishell->tab_outfile, minishell);
	if (minishell->nbr_dollars > 0)
		parse_dollars(minishell);
	if (minishell->nbr_infile != 0 || minishell->nbr_appendin != 0
		|| minishell->nbr_outfile != 0 || minishell->nbr_appendout != 0)
	{
		if (parse_redirections(minishell) == 0)
			return (0);
	}
	if (minishell->head && minishell->head != NULL)
		parse_space_quote(minishell);
	if ((minishell->tab_infile != NULL || minishell->tab_outfile != NULL))
		parse_quote_tab(minishell, &minishell->tab_infile,
			&minishell->tab_outfile);
	print_dlist(&minishell->head, &minishell->tab_infile,
		&minishell->tab_outfile, minishell);
	printf("END PARSING\n");
	return (1);
}

void	first_parse(t_shell *minishell, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] != 32)
			break ;
	if (str[i] == '\0')
		str = NULL;
	if (ft_strlen(str) > 0)
	{
		minishell->head = ft_dlstnew((void *)str);
		minishell->tail = minishell->head;
		minishell->head->prev = NULL;
		minishell->head->next = NULL;
		minishell->tail->next = NULL;
		minishell->tail->prev = NULL;
		minishell->list_size += 1;
	}
	else
	{
		minishell->head = NULL;
		minishell->tail = NULL;
	}
}
