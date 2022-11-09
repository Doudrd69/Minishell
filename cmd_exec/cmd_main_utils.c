/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_main_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 14:59:09 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/09 17:36:54 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_include/pipex_bonus.h"
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

int	set_p_status(int status, t_data *data)
{
	dprintf(2, "In set_status ==> %d\n", status);
	if (status == 2)
		return (130);
	else if (status == 32512)
		return (127);
	else
		return (0);
}

t_node *node_rotation_exec(t_node *node, t_shell *parse)
{
	while (node && node->next != NULL)
		node = node->next;
	if (parse->head != NULL)
		node = parse->head;
	else
		node = NULL;
	return (node);
}

int	start_heredoc(t_data *data, t_shell *parse)
{
	if (heredoc_main(data, &parse->tab_infile, parse) == 1)
	{
		close_hd_pipe(data, data->heredoc_nb - 1);
		free_inttab(data->hd_pipefd, data->heredoc_nb - 1);
		return (1);
	}
	return (0);
}
