/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:41:59 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/07 12:37:33 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"

int	print_var_hd(t_data *data, int var_size, char *var, int output_fd)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (var[var_size] != ' ' && var[var_size] != '\0')
	{
		if (var[var_size] == '$' && var_size != 0)
			break ;
		var_size++;
	}
	data->hd.var_length = var_size;
	data->hd.env_var = malloc(sizeof(char) * var_size);
	if (!data->hd.env_var)
		return (1);
	while (var[j] != ' ' && var[j] != '\0')
	{
		if (var[j] == '$')
			break ;
		data->hd.env_var[i] = var[j];
		i++;
		j++;
	}
	data->hd.env_var[i] = '\0';
	if (check_var_exists(j, data, output_fd) == 1)
		return (1);
	return (0);
}

int	print_var_util(t_data *data, char *str, int i, int output_fd)
{
	int		var_size;
	char	*var;

	var_size = 0;
	var = &str[i];
	print_var_hd(data, var_size, var, output_fd);
	i += data->hd.var_length;
	return (i);
}

int	check_and_print_var_hd(char *str, t_data *data, int output_fd, int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (check_eof(str) == 0)
			return (0);
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			if (str[i + 1] == ' ')
			{
				write(output_fd, &str[i], 1);
				i++;
			}
			else
				i = print_var_util(data, str, i, output_fd);
		}
		if (str[i] == '$')
			i = print_var_util(data, str, i, output_fd);
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

char	*getenv_hd(char *envp[], t_data *data, char *var_name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (i == data->envp_size)
		{
			printf("Cannot find %s\n", var_name);
			return (NULL);
		}
		if (ft_strnstr(envp[i], var_name, ft_strlen(var_name)))
			return (var_found(data, envp, var_name, i));
		i++;
	}
	printf("Cannot find %s\n", var_name);
	return (NULL);
}
//free data->home_path