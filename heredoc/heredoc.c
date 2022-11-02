/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:41:48 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/28 20:10:21 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"
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
			if (check_var(data->envp[i], data->hd.env_var))
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

void	heredoc_exit(char *str, int output_fd, t_data *data)
{
	if ((ft_strncmp(str, "test", 4) == 0))
	{
		if (check_delimiter(str, "test") == 0)
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

void	heredoc(t_data *data)
{
	struct sigaction	sa_hd;
	int					output_fd;
	char				*str;
	int					size;

	str = NULL;
	sa_hd.sa_handler = SIG_IGN;
	output_fd = data->hd_pipefd[data->hd_pipe_id][WRITE];
	sigaction(SIGQUIT, &sa_hd, NULL);
	signal(SIGINT, &sighandler_hd);
	while (1)
	{
		size = 0;
		str = readline("> ");
		if (*data->p_status == 1)
			dprintf(2, "Catch in while(1)\n");
		eof_handler_hd(data, str, output_fd);
		while (str[size])
			size++;
		if (check_and_print_var_hd(str, data, output_fd, size) == 0)
			heredoc_exit(str, output_fd, data);
		free(str);
	}
	return ;
}
