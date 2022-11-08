/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:39:41 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/08 13:17:14 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"

int	check_for_append(t_node *infile_tmp)
{
	if (infile_tmp == NULL)
		return (1);
	else if (infile_tmp->type == 'C' && infile_tmp->next == NULL)
		return (1);
	else if (infile_tmp->type == 'A' && infile_tmp->next == NULL)
		return (0);
	while (infile_tmp->next != NULL)
	{
		if (infile_tmp->type == 'A')
			return (0);
		infile_tmp = infile_tmp->next;
	}
	return (1);
}

t_node	*last_is_appendin(t_data *data, t_shell *s, t_node *tmp, t_node **i_tmp)
{
	if (data->hd.flag == 1 && s->infile_size > 0)
	{
		data->hd.index++;
		tmp = i_tmp[data->hd.index];
		data->hd.flag = 0;
	}
	else
		data->hd.flag = 1;
	return (tmp);
}

t_node	*infile_rotation(t_data *data, t_shell *s, t_node *tmp, t_node **i_tmp)
{
	if (tmp && tmp->next == NULL)
	{
		if (tmp && tmp->type == 'A')
			tmp = last_is_appendin(data, s, tmp, i_tmp);
		if (data->hd.flag == 0 && s->infile_size > 0)
		{
			if (i_tmp[data->hd.index + 1])
			{
				data->hd.index++;
				tmp = i_tmp[data->hd.index];
			}
			while (check_for_append(tmp) == 1
				&& (data->hd.index != s->infile_size + 1))
			{
				data->hd.index++;
				tmp = i_tmp[data->hd.index];
			}
		}
	}
	return (tmp);
}

int	heredoc_loop(t_data *data, t_node **infile_tmp, t_shell *parse, int ptr)
{
	int		i;
	t_node	*tmp;

	i = -1;
	tmp = infile_tmp[data->hd.index];
	while (++i < data->heredoc_nb)
	{
		data->hd_pid[i] = fork();
		if (data->hd_pid[i] == -1)
			return (1);
		while ((tmp->type != 'A') && (tmp->next != NULL))
			tmp = tmp->next;
		if (data->hd_pid[i] == 0)
			heredoc(data, tmp);
		waitpid(data->hd_pid[i], &ptr, 0);
		if (ptr != 0)
			return (1);
		if (tmp && tmp->next != NULL)
			tmp = tmp->next;
		tmp = infile_rotation(data, parse, tmp, infile_tmp);
		data->hd.check = i;
		data->hd_pipe_id++;
		data->hd_id++;
	}
	return (0);
}
