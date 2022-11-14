/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:41:00 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 10:52:28 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_tmp(int tmp)
{
	(void)tmp;
	return ;
}

int	check_eof(char *str, char *limiter)
{
	if ((ft_strncmp(str, limiter, 4) == 0))
	{
		if (check_delimiter(str, limiter) == 0)
			return (0);
	}
	return (1);
}

void	eof_handler(char *input, t_shell *minishell)
{
	if (input == NULL && minishell->list_size == 0)
	{
		free_all(minishell);
		write(2, "exit\n", 5);
		exit(0);
	}
	return ;
}

void	sigint_handler_main_loop(int signum)
{
	if (signum == 2)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sigint_handler_in_process(int signum)
{
	if (signum == 2)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}
