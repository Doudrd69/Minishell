/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:22:44 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/14 16:35:18 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	no_path(t_mini_data *data)
{
	data->home_path = getenv("HOME");
	if (data->home_path)
	{
		chdir(data->home_path);
		*data->p_status = 0;
		return (0);
	}
	return (1);
}

int	path_exists(t_mini_data *data)
{
	if (chdir(data->path) != 0)
	{
		*data->p_status = 1;
		ft_printf("minishell: cd: %s: No such file or directory\n", data->path);
		return (1);
	}
	data->cwd = getcwd(data->buff, BUF_SIZE);
	return (0);
}

int	find_position(t_mini_data *data, char *var)
{
	int	i;

	i = 0;
	while (i < data->envp_size)
	{
		if (ft_strnstr(data->env[i], var, ft_strlen(var)))
		{
			if (check_var(data->env[i], var))
				return (i);
		}
		i++;
	}
	return (i);
}

int	update_pwd(t_mini_data *data)
{
	int		position;
	int		size;
	char	*str;

	position = find_position(data, "PWD");
	if (position == data->envp_size)
		return (1);
	size = ft_strlen(data->cwd);
	str = malloc(sizeof(char) * (size + 5));
	if (!str)
		return (1);
	ft_strlcpy(str, "PWD=", 4, 0);
	ft_strlcpy(&str[4], data->cwd, size, 1);
	ft_strlcpy(data->env[position], str, ft_strlen(str), 1);
	free(str);
	return (0);
}

int	update_old_pwd(t_mini_data *data)
{
	int		position;
	int		size;
	char	*str;

	if(find_position(data, "OLDPWD") == data->envp_size) 
		check_oldpwd(data);
	else
	{
		position = find_position(data, "OLDPWD");
		if (position == data->envp_size)
			return (1);
		size = ft_strlen(data->oldpwd);
		str = malloc(sizeof(char) * (size + 8));
		if (!str)
			return (1);
		ft_strlcpy(str, "OLDPWD=", 7, 0);
		ft_strlcpy(&str[7], data->oldpwd, size, 1);
		data->env[position] = malloc(sizeof(char) * ft_strlen(str) + 1);
		if (!data->env[position])
			return (1);
		ft_strlcpy(data->env[position], str, ft_strlen(str), 1);
		free(str);
	}
	return (0);
}
