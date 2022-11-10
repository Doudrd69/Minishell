/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:00:54 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/10 12:56:11 by ebrodeur         ###   ########lyon.fr   */
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

void	sorting(char **tmp_tab)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (tmp_tab[i])
	{
		j = 0;
		while (tmp_tab[j])
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

void	display_env(char **tmp_tab)
{
	int	i;

	i = 0;
	while (tmp_tab[i])
	{
		write(1, "declare -x ", 11);
		write(1, tmp_tab[i], ft_strlen(tmp_tab[i]));
		write(1, "\n", 1);
		i++;
	}
	return ;
}


int	display_export(t_mini_data *data)
{
	int		i;
	char	**tmp_tab;

	i = 0;
	if (data->pipe_check == 0)
	{
		tmp_tab = malloc(sizeof(char *) * data->envp_size + 1);
		if (!tmp_tab)
			free(tmp_tab);
		while (i < data->envp_size)
		{
			tmp_tab[i] = ft_strdup(data->env[i]);
			i++;
		}
		tmp_tab[i] = NULL;
		sorting(tmp_tab);
		display_env(tmp_tab);
		free_tab(tmp_tab, data->envp_size);
		return (1);
	}
	return (0);
}