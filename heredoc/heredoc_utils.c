/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:41:59 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/09/29 16:57:30 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"

int	print_var_hd(t_data *data, int var_size, char *var, int output_fd)
{
	int i;
	int	j;

	i = 0;
	j = 1;
	while (var[var_size] != ' ' && var[var_size + 1] != '\0')
		var_size++;
	data->hd.var_length = var_size;
	data->hd.env_var = malloc(sizeof(char) * var_size);
	if (!data->hd.env_var)
		return (1);
	while (var[j] != ' ' && var[j] != '\0')
	{
		data->hd.env_var[i] = var[j];
		i++;
		j++;
	}
	data->hd.env_var[i] = '\0';
	if (check_var_exists(j, data, output_fd) == 1)
		return (1);
	return (0);
}

int	check_and_print_var_hd(char *str, t_data *data, int output_fd)
{
	int		i;
	int		var_size;
	char	*var;

	i = 0;
	var_size = 0;
	while (str[i])
	{
		if ((ft_strncmp(str, "test", 4) == 0))
		{
			if (check_delimiter(str, "test") == 0)
				return (0);
		}
		if (data->hd.delimiter_quotes == 0)
		{
			if (str[i] == '$' && str[i + 1] != '\0')
			{
				var = &str[i];
				print_var_hd(data, var_size, var, output_fd);
				i += data->hd.var_length;
			}
		}
		//if (output_fd != 0 && output_fd != 1)
			write(output_fd, &str[i], 1);
		i++;
	}
	write(output_fd, "\n", 1);
	//ici str[i] == \0
	return (0);
}

char	*getenv_hd(char *envp[], t_data *data, char *var_name)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = -1;
	k = 0;
	while (envp[i])
	{
		if (i == data->envp_size)
		{
			printf("Cannot find %s\n", var_name);
			return (NULL);
		}
		if (ft_strnstr(envp[i], var_name, ft_strlen(var_name)))
		{
			if (check_var(envp[i], var_name))
			{
				data->home_path = malloc(sizeof(char) * ft_strlen(envp[i]));
				if (!data->home_path)
					return (NULL);
				while (envp[i][++j])
				{
					data->home_path[k] = envp[i][j];
					k++;
				}
				data->home_path[k] = '\0';
				return (data->home_path);
			}
		}
		i++;
	}
	printf("Cannot find %s\n", var_name);
	return (NULL);
}

void	output_redirection(t_data *data)
{
	if (dup2(data->hd_pipefd[data->hd_pipe_id][WRITE], STDOUT_FILENO == -1))
	{
		perror("dup2");
		return ;
	}
	return ;
}

void	close_hd_pipe(t_data *data, int i)
{
	while (i >= 0)
	{
		close(data->hd_pipefd[i][READ]);
		close(data->hd_pipefd[i][WRITE]);
		i--;
	}
	return ;
}

//free data->home_path