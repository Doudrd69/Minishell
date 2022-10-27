/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:15:16 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/27 17:16:54 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_loop(char *str, int j)
{
	while (str[++j])
	{
		if (str[j] != 'n')
			return (1);
	}
	return (0);
}

void	*echo_arg_newline_check(t_mini_data *data, t_node *node, int check,
int loop)
{
	int	j;

	while (ft_strncmp(data->str, "-n", 2) == 0 && loop == 0)
	{
		j = 0;
		check = check_loop(data->str, j);
		if (node->next == NULL)
			return (NULL);
		if (check == 0)
		{
			data->echo_arg = 1;
			node = node->next;
			data->str = node->content;
		}
		else
		{
			data->echo_arg = 1;
			break ;
		}
	}
	return (node);
}

int	check_if_empty(t_mini_data *data)
{
	if (!data->str || (data->str[0] == '$' && data->str[1] == '\0'))
	{
		write(1, "\n", 1);
		*data->p_status = 0;
		return (0);
	}
	return (1);
}

int	echo_newline_arg(t_mini_data *data)
{
	if (data->echo_arg == 0)
	{
		write(1, "\n", 1);
		return (1);
	}
	else
		return (1);
}

int	write_and_check_signs(int i, t_mini_data *data)
{
	while (data->str[i])
	{
		data->check_print_var = 0;
		if (data->str[i] == '\0')
			return (i);
		if (data->str[i] == ' ' && data->str[i + 1] == ' ')
			i++;
		else
		{
			write(1, &data->str[i], 1);
			i++;
		}
	}
	return (i);
}
