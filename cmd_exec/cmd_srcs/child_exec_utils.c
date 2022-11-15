/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:44:07 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/15 12:00:48 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_cmd_not_found(char **param)
{
	if (param[0][0] == '/' || (ft_strncmp(param[0], "./", 2) == 0))
	{
		write(1, "minishell: ", 11);
		write(1, param[0], ft_strlen(param[0]));
		write(1, ": No such file or directory\n", 28);
		exit(127);
	}
	if (ft_strncmp(param[0], "export", 6) == 0)
		exit(0);
	write(1, "minishell: ", 11);
	write(1, param[0], ft_strlen(param[0]));
	write(1, ": command not found\n", 20);
	exit(127);
}

void	check_file(char *file)
{
	int		fd;
	char	s[1];

	fd = 0;
	if ((ft_strncmp(file, "./", 2) == 0) || (ft_strncmp(file, "/", 1) == 0))
	{
		fd = open(file, O_RDONLY);
		if (fd > 0)
		{
			if (read(fd, s, 1) < 0)
			{
				ft_printf("minishell: %s: %s\n", file, strerror(errno));
				close(fd);
				exit(errno);
			}
		}
		close(fd);
	}
	return ;
}
