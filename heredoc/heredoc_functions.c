/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:55:58 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/19 13:56:24 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"

void	eof_handler_hd(char *input)
{
	if (input == NULL)
	{
		rl_on_new_line();
		rl_redisplay();
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
