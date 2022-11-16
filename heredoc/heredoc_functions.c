/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:55:58 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/16 15:40:50 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_node	*search_first_hd(t_data *data, t_node *tmp, t_shell *parse, t_node **in)
{
	if (data->heredoc_nb == 1)
	{
		data->hd.index = search_hd(tmp, parse, in);
		tmp = in[data->hd.index];
	}
	return (tmp);
}
