/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:27:39 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 14:29:12 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../parsing/parsing.h"

void	free_tab_exec(t_data *data, t_shell *parse)
{
	if (parse->nbr_appendin > 0)
		free_inttab(data->hd_pipefd, data->heredoc_nb - 1);
	if (parse->nbr_pipe > 0)
		free_inttab(data->pipefd, parse->nbr_pipe - 1);
	if (data->check_hd > 0)
		free(data->hd_pid);
	return ;
}

void	free_if_no_list(t_data *data, t_shell *parse)
{
	if (data->exec.pipe_check > 0)
		close_pipe(data, (data->pipe_nb - 1));
	if (data->heredoc_nb > 0)
		close_hd_pipe(data, parse->nbr_appendin - 1);
	if (parse->nbr_pipe > 0)
		free_inttab(data->pipefd, parse->nbr_pipe - 1);
	return ;
}
