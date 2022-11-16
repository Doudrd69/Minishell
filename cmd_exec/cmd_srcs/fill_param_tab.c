/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 15:01:44 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/15 09:33:43 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*count_nb_of_args(t_node *node, t_data *data, int i)
{
	int		check;
	char	*tmp;

	check = 0;
	data->index_arg = 0;
	data->nb_of_args = 0;
	node = node->next;
	while (i < data->lst_size)
	{
		tmp = node->content;
		if (check == 0)
		{
			check = check_loop_exec(tmp, 0);
			data->index_arg = i;
		}
		if (check == 1)
			data->nb_of_args++;
		i++;
		if (node->next == NULL
			|| (ft_strncmp(node->next->content, "|", 4) == 0))
			break ;
		node = node->next;
	}
	node = loop_to_first_arg(node, i, data->index_arg);
	return (node);
}

int	malloc_loop_fill_param(t_node *node, char **tab, int j)
{
	tab[j] = malloc(sizeof(char) * ft_strlen(node->content) + 1);
	if (!tab[j])
	{
		free_tab(tab, j - 1);
		return (0);
	}
	return (0);
}

int	copy_args_in_param_tab(t_node *node, t_data *data, char **tab, int j)
{
	int		i;
	int		check;
	char	*tmp;

	i = -1;
	check = 0;
	if (data->nb_of_args > 0)
		node = node->next;
	while (++i < data->nb_of_args && data->nb_of_args > 0)
	{
		tmp = node->content;
		if (check == 0)
			check = check_loop_exec(tmp, 0);
		if (check == 1)
		{
			malloc_loop_fill_param(node, tab, j);
			ft_strlcpy(tab[j], node->content, ft_strlen(node->content), 1);
			j++;
		}
		node = node->next;
	}
	return (j);
}

char	**fill_param_tab(t_node *node, t_data *data, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	data->tmp_fill_tab = node->content;
	if (node->next == NULL)
		data->nb_of_args = 0;
	else if (ft_strncmp(node->next->content, "|", 1) == 0 && node->next != NULL)
		data->nb_of_args = 0;
	else if ((ft_strncmp(node->next->content, "|", 1) != 0)
		|| node->next != NULL)
		node = count_nb_of_args(node, data, i);
	else
		return (NULL);
	tab = malloc(sizeof(char *) * (data->nb_of_args + 2));
	if (!tab)
		return (NULL);
	tab[0] = malloc(sizeof(char) * ft_strlen(data->tmp_fill_tab) + 1);
	if (!tab[0])
		return (free_tab(tab, 0));
	ft_strlcpy(tab[0], data->tmp_fill_tab, ft_strlen(data->tmp_fill_tab), 1);
	j = copy_args_in_param_tab(node, data, tab, j);
	tab[j] = NULL;
	return (tab);
}
