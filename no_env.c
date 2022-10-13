/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:03:56 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/13 16:12:48 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
	if (!data->no_env[0])
		return (1);
	ft_strlcpy(data->no_env[0], "PWD=", 4, 0);
	ft_strlcpy(&data->no_env[0][4], cwd, ft_strlen(cwd), 1);
	data->no_env[1] = malloc(sizeof(char) * ft_strlen(shlvl) + 1);
	if (!data->no_env[1])
		return (2);
	ft_strlcpy(data->no_env[1], shlvl, ft_strlen(shlvl), 1);
	data->no_env[2] = malloc(sizeof(char) * ft_strlen(prog) + 1);
	if (!data->no_env[2])
		return (3);
	ft_strlcpy(data->no_env[2], prog, ft_strlen(prog), 1);
	return (0);
}