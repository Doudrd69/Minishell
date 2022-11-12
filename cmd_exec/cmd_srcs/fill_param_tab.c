/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:01:44 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/12 15:34:36 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*count_nb_of_args(t_node *node, t_data *data, int i)
{
	data->nb_of_args = 0;
	node = node->next;
	while (i < data->lst_size)
	{
		data->nb_of_args++;
		i++;
		if (node->next == NULL || ft_strncmp(node->next->content, "|", 4) == 0)
			break ;
		node = node->next;
	}
	while (--i >= 0)
		node = node->prev;
	return (node);
}

int	copy_args_in_param_tab(t_node *node, t_data *data, char **tab, int j)
{
	int	i;

	i = 0;
	if (data->nb_of_args > 0)
		node = node->next;
	while (i < data->nb_of_args && data->nb_of_args > 0)
	{
		tab[j] = malloc(sizeof(char) * ft_strlen(node->content) + 1);
		if (!tab[j])
		{
			free_tab(tab, j - 1);
			return (0);
		}
		ft_strlcpy(tab[j], node->content, ft_strlen(node->content), 1);
		node = node->next;
		j++;
		i++;
	}
	return (j);
}

char	**fill_param_tab(t_node *node, t_data *data, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (node->next == NULL)
		data->nb_of_args = 0;
	else if (ft_strncmp(node->next->content, "|", 1) == 0 && node->next != NULL)
		data->nb_of_args = 0;
	else if ((ft_strncmp(node->next->content, "|", 1) != 0)
		|| node->next != NULL)
		node = count_nb_of_args(node, data, i);
	else
		printf("Error : impossible to create PARAM TAB\n");
	tab = malloc(sizeof(char *) * (data->nb_of_args + 2));
	if (!tab)
		return (NULL);
	tab[0] = malloc(sizeof(char) * ft_strlen(node->content) + 1);
	if (!tab[0])
		return (free_tab(tab, 0));
	ft_strlcpy(tab[0], node->content, ft_strlen(node->content), 1);
	j = copy_args_in_param_tab(node, data, tab, j);
	tab[j] = NULL;
	return (tab);
}
