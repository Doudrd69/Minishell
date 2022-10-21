/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:15:16 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/21 13:06:57 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

int	backslash_specific_cases(t_mini_data *data, int i)
{
	if (data->str[i] == '\\' && data->str[i + 1] == '$')
	{
		i++;
		write(1, &data->str[i], 1);
		i++;
	}
	if (data->str[i] == '\\' && data->str[i + 1] == '\\')
		i++;
	if (data->str[i] == '$' && data->str[i + 1] == '\\')
	{
		write(1, &data->str[i], 1);
		i += 2;
	}
	return (i);
}

int	check_and_print_var(int i, t_mini_data *data)
{
	int		j;
	int		size;
	int		tmp;
	char	*position;

	j = 0;
	size = 0;
	tmp = i;
	i = specific_cases_with_special_char(data, i);
	if (i > tmp)
		return (i);
	position = &data->str[i];
	while (position[size] != '\0' && position[size] != ' ')
	{
		if (check_special_char(position[size], size) == 1)
			break ;
		size++;
	}
	j = var_search_copy(data, size, i, j);
	print_var(j, data);
	i = data->tmp_count;
	if (data->check_print_var != 1
		&& data->str[i] == ' ' && data->str[i + 1] != '$')
		i++;
	return (i);
}

int	check_signs(int i, t_mini_data *data)
{
	if (data->str[i] == '$' && data->str[i + 1] != '\0')
	{
		i = check_and_print_var(i, data);
		if (data->check_print_var == 1)
		{
			if (data->str[i] == '\0')
				return (i);
		}
		while (data->str[i] == '$')
			i = check_and_print_var(i, data);
		if (data->str[i] == '\\' && data->str[i + 1] == '$')
		{
			i++;
			write(1, &data->str[i], 1);
			i++;
		}
		if (data->str[i + 1] == '\0')
			return (echo_newline_arg(data));
	}
	return (i);
}

int	write_and_check_signs(int i, t_mini_data *data)
{
	while (data->str[i])
	{
		data->check_print_var = 0;
		i = backslash_specific_cases(data, i);
		//i = check_signs(i, data);
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
