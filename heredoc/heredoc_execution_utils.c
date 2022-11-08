/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:39:41 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/08 20:54:49 by ebrodeur         ###   ########lyon.fr   */
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

void	search_hd(t_node *tmp, t_shell *parse, t_node **tab)
{
	int	i;
	int	check;
	int	tmp1;
	int	tmp2;

	i = 0;
	check = 0;
	tmp1 = 0;
	tmp2 = 0;
	printf("infile size : %d\n", parse->infile_size);
	while (i < parse->infile_size)
	{
		tmp = tab[i];
		while (tmp != NULL)
		{
			printf("==> %s [%d][%d]\n", tmp->content, i, check);
			if (tmp->type == 'A')
			{
				tmp1 = check;
				break ;
			}
			check++;
			tmp = tmp->next;
		}
		check = 0;
		i++;
	}
	tmp2 = i;
	printf("Hd at [%d][%d]\n", tmp2, tmp1);
}

t_node	*infile_rotation(t_data *data, t_node *tmp, t_node **i_tmp)
{
	if (tmp->type == 'C' && tmp->next == NULL)
	{
		data->hd.index++;
		tmp = i_tmp[data->hd.index];
	}
	else if (tmp->type == 'A' && tmp->next == NULL)
		tmp = tmp->next;
	else
	{
		while (tmp->next != NULL && (tmp->type != 'A'))
			tmp = tmp->next;
	}
	return (tmp);
}

t_node	*rotation_after_exec(t_node *tmp, t_data *data, t_node **in, t_shell *s)
{
	if (tmp->next != NULL && tmp->next->type == 'A')
		tmp = tmp->next;
	else if (tmp->next != NULL && tmp->next->type == 'C')
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
		{
			data->hd.index++;
			tmp = in[data->hd.index];
		}
		else if (tmp->next != NULL)
		{
			while (tmp->next != NULL && (tmp->type != 'A'))
				tmp = tmp->next;
		}
	}
	else
	{
		if (data->hd.index < s->infile_size)
		{
			data->hd.index++;
			tmp = in[data->hd.index];
		}
	}
	return (tmp);
}

int	heredoc_process(t_node *tmp, t_data *data, int i, int ptr)
{
	if (tmp && tmp->type == 'A')
	{
		if (data->hd_pid[i] == 0)
			heredoc(data, tmp);
		waitpid(data->hd_pid[i], &ptr, 0);
		if (ptr != 0)
			return (1);
	}
	return (0);
}

int	heredoc_loop(t_data *data, t_node **infile_tmp, t_shell *parse, int ptr)
{
	int		i;
	t_node	*tmp;

	i = -1;
	//si HD == 1 et tab[0..n]==NULL --> on se met direct sur le bon
	tmp = infile_tmp[data->hd.index];
	search_hd(tmp, parse, infile_tmp);
	while (++i < data->heredoc_nb)
	{
		data->hd_pid[i] = fork();
		if (data->hd_pid[i] == -1)
			return (1);
		if (tmp == NULL && (data->hd.index < parse->infile_size))
		{
			data->hd.index++;
			tmp = infile_tmp[data->hd.index];
		}
		if (tmp && tmp->type != 'A')
			tmp = infile_rotation(data, tmp, infile_tmp);
		if (heredoc_process(tmp, data, i, ptr) == 1)
			return (1);
		tmp = rotation_after_exec(tmp, data, infile_tmp, parse);
		data->hd.check = i;
		data->hd_pipe_id++;
		data->hd_id++;
	}
	return (0);
}
