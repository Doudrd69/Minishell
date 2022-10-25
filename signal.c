/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:41:00 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/25 14:14:55 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_eof(char *str)
{
	if ((ft_strncmp(str, "test", 4) == 0))
	{
		if (check_delimiter(str, "test") == 0)
			return (0);
	}
	return (1);
}

void	eof_handler(char *input, t_shell *minishell)
{
	if (input == NULL)
	{
		free_all(minishell);
		write(2, "exit\n", 5);
		exit(0);
	}
	return ;
}

void	sighandler(int signum)
{
	if (signum == 2)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sighandler_hd(int signum)
{
	(void)signum;
	exit(1);
	//si plusieurs HD, on quitte TOUT
	//mini_exit(2);
}