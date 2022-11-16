/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:41:48 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/16 15:40:42 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>

int	var_exists_hd(t_data *data)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strlen(data->hd.env_var);
	while (i < data->envp_size)
	{
		if (ft_strnstr(data->envp[i], data->hd.env_var, size))
		{
			if (check_var_hd(data->envp[i], data->hd.env_var))
			{
				data->hd.position = i;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	write_var_value(t_data *data, int output_fd, int j, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (output_fd != 0 && output_fd != 1)
			write(output_fd, &data->hd.env_var_value[++j], 1);
		i++;
	}
	return ;
}

int	check_var_exists(int j, t_data *data, int output_fd)
{
	int	size;

	j = 0;
	if (var_exists_hd(data) == 0)
	{
		data->hd.env_var_value = getenv_hd(data->envp, data, data->hd.env_var);
		if (data->hd.env_var_value == NULL)
		{
			free(data->hd.env_var);
			return (1);
		}
		while (data->hd.env_var_value[j] != '=')
			j++;
		size = ft_strlen(&data->hd.env_var_value[j]);
		write_var_value(data, output_fd, j, size);
		free(data->hd.env_var);
		return (0);
	}
	free(data->hd.env_var);
	return (1);
}

void	heredoc_exit(char *str, char *limiter, int output_fd, t_data *data)
{
	if ((ft_strncmp(str, limiter, 4) == 0))
	{
		if (check_delimiter(str, limiter) == 0)
		{
			free(str);
			close(output_fd);
			close(data->hd_pipefd[data->hd_pipe_id][READ]);
			data->p_status = 0;
			exit(0);
		}
	}
	return ;
}

void	heredoc(t_data *data, t_node *tmp)
{
	struct sigaction	sa_hd;
	int					output_fd;
	char				*str;
	int					size;

	str = NULL;
	sa_hd.sa_handler = SIG_IGN;
	sa_hd.sa_flags = 0;
	sa_hd.sa_mask = 0;
	output_fd = data->hd_pipefd[data->hd_pipe_id][WRITE];
	data->hd.limiter = tmp->content;
	sigaction(SIGQUIT, &sa_hd, NULL);
	signal(SIGINT, &sighandler_hd);
	while (1)
	{
		size = 0;
		str = readline("> ");
		eof_handler_hd(data, str, output_fd);
		while (str[size])
			size++;
		if (check_and_print_var_hd(str, data, output_fd, size) == 0)
			heredoc_exit(str, data->hd.limiter, output_fd, data);
		free(str);
	}
	exit(1);
}
