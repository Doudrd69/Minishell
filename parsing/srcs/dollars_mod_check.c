/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_mod_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:46:22 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/17 20:04:28 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static void	test(t_shell *minishell, int check, t_node **list, int i)
{
	printf("minishell->mod ==%d\n", minishell->mod);
	write_newvalue(minishell, minishell->stra + i, check, i);
	change_var_to_value(minishell->stra, i, minishell, list);
}

char	*interpret_dollars(char *str, int i,
		t_shell *minishell, t_node **list)
{
	int	check;

	minishell->stra = str;
	if (check_dquote_mod(str, i) == 0)
		return (NULL);
	check_and_print_var_parsing(minishell, str + i);
	if (minishell->value)
		change_var_to_value(str, i, minishell, list);
	else
	{
		check = value_check_with_mod(str, i);
		if ((minishell->mod == 2 || minishell->mod == 3)
			&& str[i + 1] == ' ')
		{
			return (str + 1);
			check = 6;
			write_newvalue(minishell, str, check, i);
			change_value_mod2_and_3(str, i, minishell, list);
		}
		else
			test(minishell, check, list, i);
	}
	return (str);
}

static void	other_dollars_mod(t_shell *minishell,
	int i, t_node **list, int check)
{
	if (minishell->mod == 1)
	{
		value_quote_mod_1(minishell, minishell->stro, i);
		change_value_mod1(minishell->stro, i, minishell, list);
	}
	else
	{
		write_newvalue(minishell, minishell->stro + i, check, i);
		change_var_to_value(minishell->stro, i, minishell, list);
	}
}

char	*dollars_mod(char *str, int i, t_shell *minishell, t_node **list)
{
	int	check;

	minishell->stro = str;
	if (minishell->mod == 8)
		return (str);
	if (minishell->mod == 0 || minishell->mod == 2
		|| minishell->mod == 4 || minishell->mod == 3)
	{
		str = interpret_dollars(str, i, minishell, list);
	}
	else
	{
		if (check_quote_mod(str, i) == 0)
			return (str);
		check = check_dollars_mod(str + i);
		other_dollars_mod(minishell, i, list, check);
	}
	return (str);
}
