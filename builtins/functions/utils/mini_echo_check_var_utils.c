/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_echo_check_var_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 11:16:32 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/19 13:23:49 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	pid_display(t_mini_data *data, int i)
{
	char	*pid;

	if (data->str[i] == '$' && data->str[i + 1] == '$')
	{
		pid = ft_itoa(getpid());
		write(1, pid, ft_strlen(pid));
		free(pid);
		return (i += 2);
	}
	return (i);
}

int	specific_cases_with_special_char(t_mini_data *data, int i)
{
	if (data->str[i + 1] == '?')
	{
		ft_printf("%d", *data->p_status);
		return (i + 2);
	}
	if (data->str[i + 1] <= '9' && data->str[i + 1] >= '0')
		return (i + 2);
	if (data->str[i] == '$' && data->str[i + 1] == '$')
	{
		i = pid_display(data, i);
		return (i);
	}
	if (data->str[i] == '$' && data->str[i + 1] == ' ')
	{
		write(1, &data->str[i], 1);
		return (i + 1);
	}
	return (i);
}

int	var_exists(t_mini_data *data)
{
	int	i;

	i = 0;
	while (i < data->envp_size)
	{
		if (ft_strnstr(data->env[i],
				data->var_search, ft_strlen(data->var_search)))
		{
			if (check_var(data->env[i], data->var_search))
				return (1);
		}
		i++;
	}
	return (0);
}

int	var_search_copy(t_mini_data *data, int size, int i, int j)
{
	data->var_search = malloc(sizeof(char) * size);
	if (!data->var_search)
		return (1);
	i++;
	while (data->str[i] != ' ' && data->str[i] != '\0')
	{
		if (check_special_char(data->str[i], size) == 1)
			break ;
		data->var_search[j] = data->str[i];
		i++;
		j++;
	}
	data->var_search[j] = '\0';
	data->tmp_count = i;
	return (j);
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
