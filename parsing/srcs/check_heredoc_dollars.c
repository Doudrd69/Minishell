/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc_dollars.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:17:46 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/18 12:41:09 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	value_check_with_mod(t_shell *minishell, char *str, int i)
{
	int	check;

	check = check_dollars_mod(minishell, str + i);
	if (check == 2)
	{
		check = check_dollar_export(str, i);
	}
	return (check);
}

int	check_dquote_mod(char *str, int i)
{
	if (check_heredoc_dollar_mod_2_3(str, i) == 0)
		return (0);
	if (check_heredoc_dollar_mod(str, i) == 0)
		return (0);
	return (1);
}

int	check_quote_mod(char *str, int i)
{
	if (check_heredoc_dollar_mod_1(str, i) == 0)
		return (0);
	if (check_heredoc_dollar_mod(str, i) == 0)
		return (0);
	return (1);
}
