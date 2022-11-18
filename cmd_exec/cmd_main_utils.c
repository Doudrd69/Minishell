/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_main_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:59:09 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 09:04:40 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigtest(int signum)
{
	(void)signum;
	write(1, "Quit : 3\n", 9);
}

int	fork_creation(int pid)
{
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error : fork failed\n");
		exit(1);
	}
	return (pid);
}

int	set_p_status(int status, t_node *node)
{
	int	tmp;

	tmp = 0;
	while (node && node->next != NULL)
		node = node->next;
	if (node && node->prev != NULL
		&& ft_strncmp(node->prev->content, "exit", 4) == 0)
		tmp = ft_atoi(node->content);
	if (status == 768 || status == 13)
		return (tmp);
	else if (status == 65280)
		return (255);
	else if (status == 3)
		return (131);
	else if (status == 5376)
		return (126);
	else if (status == 2)
		return (130);
	else if (status == 32512)
		return (127);
	else if (status == 1 || status == 3328 || status == 256)
		return (1);
	else
		return (0);
}

t_node	*node_rotation_exec(t_node *node, t_shell *parse)
{
	if (parse->head != NULL)
		node = parse->head;
	else
		node = NULL;
	return (node);
}

int	start_heredoc(t_data *data, t_shell *parse, t_node *node)
{
	if (parse->nbr_appendin > 0)
		data->check_hd = 1;
	else
		data->check_hd = 0;
	if (heredoc_main(data, &parse->tab_infile, parse) == 1)
	{
		close_hd_pipe(data, data->heredoc_nb - 1);
		free_inttab(data->hd_pipefd, data->heredoc_nb - 1);
		free(data->hd_pid);
		return (1);
	}
	if (parse->outfile_size == 0 && node == NULL)
	{
		close_hd_pipe(data, data->heredoc_nb - 1);
		free_inttab(data->hd_pipefd, data->heredoc_nb - 1);
		free(data->hd_pid);
		return (1);
	}
	return (0);
}
