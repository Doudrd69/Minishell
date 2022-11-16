/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 13:47:24 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/16 12:22:47 by ebrodeur         ###   ########lyon.fr   */
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

void	*echo_arg_newline_check(t_data *data, t_node *node, int check,
int loop)
{
	int	j;

	while (ft_strncmp(data->str, "-n", 2) == 0 && loop == 0)
	{
		j = 0;
		check = check_loop(data->str, j);
		if (check == 0)
		{
			data->echo_arg = 1;
			if (node->next != NULL)
				node = node->next;
			else
				return (NULL);
			data->str = node->content;
		}
		else
		{
			if (node->next == NULL || ft_strncmp(node->content, "-n", 2) == 0)
				break ;
			data->echo_arg = 1;
			break ;
		}
	}
	return (node);
}

int	check_if_empty(t_data *data)
{
	if (!data->str || (data->str[0] == '$' && data->str[1] == '\0'))
	{
		write(1, "\n", 1);
		data->p_status = 0;
		return (0);
	}
	return (1);
}

int	write_and_check_signs(int i, t_data *data)
{
	char	*tmp;

	while (data->str[i])
	{
		if (data->str[i] == '$' && data->str[i + 1] == '?')
		{
			if (*data->test == 1)
				tmp = ft_itoa(*data->test);
			else
				tmp = ft_itoa(data->p_status);
			write(data->output_fd, tmp, ft_strlen(tmp));
			i += 2;
		}
		data->check_print_var = 0;
		if (data->str[i] == '\0')
			return (i);
		if (data->str[i] == ' ' && data->str[i + 1] == ' ')
			i++;
		else
		{
			write(data->output_fd, &data->str[i], 1);
			i++;
		}
	}
	return (i);
}
