/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:51:45 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/12 15:34:40 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*strjoin_arg(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!(s1) || !(s2))
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!(str))
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '/';
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**join_arg(char **tab, char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		args[i] = strjoin_arg(args[i], tab[0]);
	return (args);
}

char	**get_path(char *env[], t_data *data, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (i < data->envp_size)
	{
		if (ft_strnstr(env[i], "PATH", 4))
		{
			data->env.path = malloc(sizeof(char) * (ft_strlen(env[i]) + 1));
			if (!data->env.path)
				return (NULL);
			while (env[i][++j])
				data->env.path[j] = env[i][j];
			data->env.path[j] = '\0';
			args = ft_split(&data->env.path[5], ':');
			if (!args)
				return (NULL);
			free(data->env.path);
			return (args);
		}
		i++;
	}
	return (NULL);
}

int	**free_inttab(int **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (0);
}

void	close_pipe(t_data *data, int i)
{
	while (i >= 0)
	{
		close(data->pipefd[i][READ]);
		close(data->pipefd[i][WRITE]);
		i--;
	}
	return ;
}
