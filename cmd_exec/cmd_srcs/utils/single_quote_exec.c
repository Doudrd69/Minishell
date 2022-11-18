/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:28:56 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 13:25:56 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	multi_cmd_dup_to_pipe(t_data *data, int index)
{
	if (dup2(data->pipefd[index - 1][READ], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	return (0);
}
