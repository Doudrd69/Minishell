/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:00:54 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/12 20:34:29 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	sorting(char **tmp_tab, int size)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (ft_strcmp(tmp_tab[i], tmp_tab[j]) < 0)
			{
				tmp = tmp_tab[i];
				tmp_tab[i] = tmp_tab[j];
				tmp_tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return ;
}

void	display_env(char **tmp_tab, int size, int output_fd)
{
	int	i;

	i = 0;
	while (i < size)
	{
		write(output_fd, "declare -x ", 11);
		write(output_fd, tmp_tab[i], ft_strlen(tmp_tab[i]));
		write(output_fd, "\n", 1);
		i++;
	}
	return ;
}


int	display_export(t_data *data)
{
	int		i;
	int		output_fd;
	char	**tmp_tab;

	i = 0;
	if (data->pipe_check == 1)
		output_fd = data->pipefd[0][WRITE];
	else
		output_fd = 1;
	tmp_tab = malloc(sizeof(char *) * data->envp_size + 1);
	if (!tmp_tab)
		free(tmp_tab);
	while (i < data->envp_size)
	{
		tmp_tab[i] = ft_strdup(data->envp[i]);
		i++;
	}
	tmp_tab[i] = NULL;
	sorting(tmp_tab, data->envp_size);
	display_env(tmp_tab, data->envp_size, output_fd);
	free_tab(tmp_tab, data->envp_size);
	if (data->pipe_check == 1)
		return (0);
	return (1);
}