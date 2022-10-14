/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:03:56 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/14 16:23:57 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	create_oldpwd(t_mini_data *data)
{
	char	*str;

	str = malloc(sizeof(char) * (ft_strlen(data->oldpwd) + 8));
	if (!str)
		return (1);
	ft_strlcpy(str, "OLDPWD=", 7, 0);
	ft_strlcpy(&str[7], data->oldpwd, ft_strlen(data->oldpwd), 1);
	mini_export(data, str);
	data->env = data->new_env;
	data->first_cd_check = 1;
	free(str);
	return (0);
}

int	check_oldpwd(t_mini_data *data)
{
	if (data->no_env_check == 1 && data->first_cd_check == 0)
	{
		if (create_oldpwd(data) == 1)
			return (1);
	}
	return (0);
}

int	check_malloc(t_mini_data *data, int i)
{
	if (!data->no_env[i])
	{
		free_tab(data->no_env, i);
		return (1);
	}
	return (0);
}

int	export_no_env(t_mini_data *data, char **envp)
{
	char	*cwd;
	char	*shlvl;
	char	*prog;

	data->no_env = malloc(sizeof(char *) * 3);
	if (!data->no_env)
		return (1);
	cwd = getcwd(data->buff, BUF_SIZE);
	shlvl = mini_getenv(envp, data, "SHLVL");
	prog = mini_getenv(envp, data, "_");
	data->no_env[0] = malloc(sizeof(char) * ft_strlen(cwd) + 5);
	if (check_malloc(data, 0) == 1)
		return (1);
	ft_strlcpy(data->no_env[0], "PWD=", 4, 0);
	ft_strlcpy(&data->no_env[0][4], cwd, ft_strlen(cwd), 1);
	data->no_env[1] = malloc(sizeof(char) * ft_strlen(shlvl) + 1);
	if (check_malloc(data, 1) == 1)
		return (1);
	ft_strlcpy(data->no_env[1], shlvl, ft_strlen(shlvl), 1);
	data->no_env[2] = malloc(sizeof(char) * ft_strlen(prog) + 1);
	if (check_malloc(data, 2) == 1)
		return (1);
	ft_strlcpy(data->no_env[2], prog, ft_strlen(prog), 1);
	free(shlvl);
	return (0);
}
