/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_mod_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:46:22 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 13:37:37 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	value_check_with_mod(char *str, int i)
{
	int	check;

	check = check_dollars_mod(str + i);
	if (check == 2)
		check = check_dollar_export(str, i);
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

int	interpret_dollars(char *str, int i,
		t_shell *minishell, t_node **list)
{
	int	check;

	if (check_dquote_mod(str, i) == 0)
		return (0);
	check_and_print_var_parsing(minishell, str + i);
	if (minishell->value)
		change_var_to_value(str, i, minishell, list);
	else
	{
		check = value_check_with_mod(str, i);
		if ((minishell->mod == 2 || minishell->mod == 3)
			&& str[i + 1] == ' ')
		{
			check = 6;
			write_newvalue(minishell, str, check, i);
			change_value_mod2_and_3(str, i, minishell, list);
		}
		else
		{
			write_newvalue(minishell, str + i, check, i);
			change_var_to_value(str, i, minishell, list);
		}
	}
	return (1);
}

char	*dollars_mod(char *str, int i, t_shell *minishell, t_node **list)
{
	int	check;

	if (minishell->mod == 0 || minishell->mod == 2
		|| minishell->mod == 4 || minishell->mod == 3)
	{
		if (interpret_dollars(str, i, minishell, list) == 0)
			return (str);
	}
	else
	{
		if (check_quote_mod(str, i) == 0)
			return (str);
		check = check_dollars_mod(str + i);
		if (minishell->mod == 1)
		{
			value_quote_mod_1(minishell, str, i);
			change_value_mod1(str, i, minishell, list);
		}
		else
		{
			write_newvalue(minishell, str + i, check, i);
			change_var_to_value(str, i, minishell, list);
		}
	}
	return (str);
}
