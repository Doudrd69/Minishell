/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:55:58 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/10 08:14:22 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"

void	eof_handler_hd(t_data *data, char *input, int output_fd)
{
	if (input == NULL)
	{
		close(output_fd);
		close(data->hd_pipefd[data->hd_pipe_id][READ]);
		data->p_status = 0;
		exit (0);
	}
	return ;
}

int	check_delimiter(char *str, char *delimiter)
{
	size_t	size;

	size = 0;
	while (str[size])
		size++;
	if (size == ft_strlen(delimiter))
		return (0);
	return (1);
}

int	check_var_hd(char *str, char *var_name)
{
	size_t	size;

	size = 0;
	while (str[size] != '=')
		size++;
	if (size == ft_strlen(var_name))
		return (1);
	return (0);
}
