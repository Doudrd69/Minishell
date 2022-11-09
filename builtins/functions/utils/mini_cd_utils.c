/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:22:44 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/09 14:25:46 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	no_path(t_mini_data *data)
{
	int	i;

	i = 0;
	data->home_path = mini_getenv(data->env, data, "HOME");
	if (data->home_path)
	{
		while (data->home_path[i])
		{
			if (data->home_path[i] == '=')
				break ;
			i++;
		}
		i++;
		chdir(&data->home_path[i]);
		data->cwd = getcwd(data->buff_oldpwd, BUF_SIZE);
		data->p_status = 0;
		return (0);
	}
	return (1);
}

int	path_exists(t_mini_data *data, t_node *node)
{
	if (chdir(node->content) != 0)
	{
		data->p_status = 1;
		ft_printf("minishell: cd: %s: ", node->content);
		ft_printf("No such file or directory\n");
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
	size_t	size;
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
	if (size > ft_strlen(data->env[position]))
	{
		data->env[position] = str;
		return (0);
	}
	else
		ft_strlcpy(data->env[position], str, ft_strlen(str), 1);
	free(str);
	return (0);
}

int	update_old_pwd(t_mini_data *data)
{
	int		position;
	size_t	size;
	char	*str;

	if (find_position(data, "OLDPWD") == data->envp_size)
	{
		if (check_oldpwd(data) == 1)
			return (1);
	}
	else
	{
		position = find_position(data, "OLDPWD");
		size = ft_strlen(data->oldpwd);
		str = malloc(sizeof(char) * (size + 8));
		if (!str)
			return (1);
		str = oldpwd_copy(data, str, size);
		if (check_length(data, size, position, str) == 0)
			return (0);
		else
			ft_strlcpy(data->env[position], str, ft_strlen(str), 1);
		free(str);
	}
	return (0);
}
