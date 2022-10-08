/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:15:16 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/09/29 12:57:12 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


int	var_exists(t_mini_data *data)//a modifier pour etre utilisable partout
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], data->var_search, ft_strlen(data->var_search)))
		{
			if (check_var(data->env[i], data->var_search))
				return (1);
		}
		i++;
	}
	return (0);
}

void	print_var(int j, t_mini_data *data)
{
	if (var_exists(data))
	{
		j = 0;
		data->echo_var = mini_getenv(data->env, data, data->var_search);
		while (data->echo_var[j] != '=')
			j++;
		while (data->echo_var[++j])
			write(1, &data->echo_var[j], 1);
		data->check_print_var = 1;
		free(data->home_path);
	}
	free(data->var_search);
	return ;
}

int	check_and_print_var(int i, t_mini_data *data)
{
	int		size;
	int		j;
	char	*position;

	j = 0;
	size = 0;
	if (data->str[i + 1] == '?')
	{
		ft_printf("%d", *data->p_status);
		return (i + 2);
	}
	if (data->str[i + 1] <= '9' && data->str[i + 1] >= '0')
		return (i + 2);
	position = &data->str[i];//position du $
	while (position[size] != '\0' && position[size] != ' ')
	{
		if (position[size] == '$' && size != 0)
			break ;
		size++;
	}
	data->var_search = malloc(sizeof(char) * size);//pas de +1 car le '\0' prend la place du $
	if (!data->var_search)
		return (1);
	i++;
	while (data->str[i] != ' ' && data->str[i] != '\0')
	{
		if (data->str[i] == '$' && i != 0)
			break ;
		data->var_search[j] = data->str[i];
		i++;
		j++;
	}
	data->var_search[j] = '\0';
	print_var(j, data);
	if (data->check_print_var != 1 && data->str[i] == ' ' && data->str[i + 1] != '$')
		i++;
	return (i);
}

int	check_signs(int i, t_mini_data *data)
{
	if (data->str[i] == '$' && data->str[i + 1] != '\0' && data->echo_sq_check == 0)
	{
		i = check_and_print_var(i, data);
		if (data->check_print_var == 1)
		{
			if (data->str[i] == '\0')
				return (i);
		}
		if (data->str[i] == '$')//plusieurs $ dans le meme mot
			i = check_and_print_var(i, data);
		if (data->str[i + 1] == '\0')
		{
			if (data->echo_arg == 0)
			{
				write(1, "\n", 1);
				return (1);
			}
			else
				return (1);
		}
	}
	return (i);
}

int	write_and_check_signs(int i, t_mini_data *data)
{
	while (data->str[i])
	{
		data->check_print_var = 0;
		if (data->str[i] == '\\')
			i++;
		i = check_signs(i, data);
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