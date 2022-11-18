/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:44:07 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 13:09:45 by ebrodeur         ###   ########lyon.fr   */
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
	write(2, "minishell: ", 11);
	write(2, param[0], ft_strlen(param[0]));
	write(2, ": command not found\n", 20);
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

void	free_and_exit_builtin(char **arg_tab, char **param, int p_size)
{
	int	size;

	size = 0;
	free_tab(param, p_size);
	while (arg_tab[size])
		size++;
	free_tab(arg_tab, size - 1);
	exit (0);
}

void	cmd_exec_path(t_data *data, int pipe_id)
{
	close_pipe(data, pipe_id);
	check_file(data->env.param_tab3[0]);
	if (execve(data->env.param_tab3[0], data->env.param_tab3,
			data->envp) == -1)
		{
			perror("execve");
			exit(errno);
		}
}

void	close_pipe_hd_before_dup(t_data *data, t_shell *parse)
{
	close(data->hd_pipefd[0][0]);
	close(data->hd_pipefd[0][1]);
	data->hd_pipefd[0][0] = dup(data->hd_pipefd[parse->nbr_appendin - 1][0]);
	data->hd_pipefd[0][1] = dup(data->hd_pipefd[parse->nbr_appendin - 1][1]);
	return ;
}
