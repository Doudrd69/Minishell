/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:51:45 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/09/14 10:41:32 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_include/pipex_bonus.h"

void	exec_cmd(char **tab, char **param, char *env[], t_data *data)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (access(tab[i], X_OK) == 0)
		{
			if (execve(tab[i], param, env) == -1)
				perror("execve");
		}
		i++;
	}
	write(2, "minishell : command not found\n", 30);
	*data->p_status = 127;
	exit(127);
}

char	**join_arg(char **tab, char **args)//je recup les chenins et je colle ma commande a la fin pour l'exec
{
	int	i;

	i = -1;
	while (args[++i])
		args[i] = ft_strjoin(args[i], tab[0]);
	return (args);
}

char	**get_path(char *env[], t_data *data, char **args)//gerer le cas ou pas d'env
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (env[i])
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
