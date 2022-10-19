/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:41:59 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/19 13:50:39 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"

int	copy_var_hd(t_data *data, char *var, int j)
{
	int	i;

	i = 0;
	while (var[j] != ' ' && var[j] != '\0')
	{
		if (check_special_char(var[j], 1))
			break ;
		data->hd.env_var[i] = var[j];
		i++;
		j++;
	}
	data->hd.env_var[i] = '\0';
	return (j);
}

int	print_var_hd(t_data *data, int var_size, char *var, int output_fd)
{
	int	j;

	j = 1;
	while (var[var_size] != ' ' && var[var_size] != '\0')
	{
		if (check_special_char(var[var_size], var_size) == 1)
			break ;
		var_size++;
	}
	if (var_size <= 1)
		return (2);
	data->hd.var_length = var_size;
	data->hd.env_var = malloc(sizeof(char) * var_size);
	if (!data->hd.env_var)
		return (1);
	j = copy_var_hd(data, var, j);
	if (check_var_exists(j, data, output_fd) == 1)
		return (1);
	return (0);
}

int	print_var_util(t_data *data, char *str, int i, int output_fd)
{
	int		var_size;
	char	*var;
	char	*pid;

	var_size = 0;
	var = &str[i];
	if (str[i] == '$' && str[i + 1] == '$')
	{
		pid = ft_itoa(getpid());
		write(output_fd, pid, ft_strlen(pid));
		return (i += 2);
	}
	if (str[i + 1] <= '9' && str[i + 1] >= '0')
		return (i + 2);
	if (print_var_hd(data, var_size, var, output_fd) == 2)
		return (i);
	i += data->hd.var_length;
	return (i);
}

int	check_and_print_var_hd(char *str, t_data *data, int output_fd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		data->hd.bkslash_check = 0;
		if (check_eof(str) == 0)
			return (0);
		i = backslash_check(data, str, i);
		if (str[i] == '$' && str[i + 1] != '\0' && data->hd.bkslash_check == 0)
			i = cpvhd_specific_cases(data, str, i, output_fd);
		if (str[i] != '\0')
			write(output_fd, &str[i], 1);
		i++;
	}
	write(output_fd, "\n", 1);
	return (0);
}

char	*var_found(t_data *data, char *envp[], char *var_name, int i)
{
	int	j;
	int	k;

	j = -1;
	k = 0;
	if (check_var(envp[i], var_name))
	{
		data->home_path = malloc(sizeof(char) * ft_strlen(envp[i]) + 1);
		if (!data->home_path)
			return (NULL);
		while (envp[i][++j])
		{
			data->home_path[k] = envp[i][j];
			k++;
		}
		data->home_path[k] = '\0';
		return (data->home_path);
	}
	return (NULL);
}
