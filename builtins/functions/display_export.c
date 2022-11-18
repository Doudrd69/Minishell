/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:00:54 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 12:41:29 by ebrodeur         ###   ########lyon.fr   */
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

int	display_export(t_data *data, char ***tab)
{
	int		i;
	int		output_fd;
	char	**tmp_tab;

	i = 0;
	output_fd = 1;
	tmp_tab = *tab;
	sorting(tmp_tab, data->envp_size);
	display_env(tmp_tab, data->envp_size, output_fd);
	if (data->pipe_check == 1)
		return (3);
	return (1);
}
