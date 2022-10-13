/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:41:00 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/13 15:41:19 by ebrodeur         ###   ########lyon.fr   */
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

void	eof_handler(char *input)//si dans HD, ou un sleep ---> attendre fin des processus? free?
{
	if (input == NULL)
	{
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
		rl_replace_line("", 0);//on remplace le buffer de readline (rl_line_buffer)
		rl_on_new_line();
		rl_redisplay();
	}
}
//rl_line_buffer = vide quand on C-c

void	sighandler_hd(int signum)
{
	if (signum == SIGINT)
	{
		//on est dans le process sur HD
		mini_exit(2);
	}
	//si on doit ecrire dans un document, on le unlink?
}