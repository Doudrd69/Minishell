/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:00:54 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 13:50:06 by ebrodeur         ###   ########lyon.fr   */
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
	while (i < size - 1)
	{
		j = 0;
		while (j < size - 1)
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
	while (i < size - 1)
	{
		write(output_fd, "declare -x ", 11);
		write(output_fd, tmp_tab[i], ft_strlen(tmp_tab[i]));
		write(output_fd, "\n", 1);
		i++;
	}
	return ;
}

int	loop_copy_export(t_data *data, char **tmp_tab)
{
	int	i;

	i = 0;
	while (i < data->envp_size - 1)
	{
		tmp_tab[i] = malloc(sizeof(char) * ft_strlen(data->envp[i]) + 1);
		if (!tmp_tab[i])
		{
			free_tab(tmp_tab, i - 1);
			return (1);
		}
		ft_strlcpy(tmp_tab[i], data->envp[i], ft_strlen(data->envp[i]), 1);
		i++;
	}
	tmp_tab[i] = NULL;
	return (0);
}

int	display_export(t_data *data)
{
	int		i;
	int		output_fd;
	char	**tmp_tab;

	i = 0;
	output_fd = 1;
	tmp_tab = malloc(sizeof(char *) * data->envp_size + 1);
	if (!tmp_tab)
		return (1);
	if (loop_copy_export(data, tmp_tab) == 1)
		return (1);
	sorting(tmp_tab, data->envp_size);
	display_env(tmp_tab, data->envp_size, output_fd);
	free_tab(tmp_tab, i - 1);
	if (data->pipe_check == 1)
		return (3);
	return (1);
}
