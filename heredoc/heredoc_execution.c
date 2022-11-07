/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:04:20 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/07 15:49:05 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_exec/cmd_include/pipex_bonus.h"

char	*getenv_hd(char *envp[], t_data *data, char *var_name)
{
	if (ft_strnstr(envp[data->hd.position], var_name, ft_strlen(var_name)))
		return (var_found(data, envp, var_name, data->hd.position));
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

int	hd_pipe_creation(t_data *data)
{
	int	i;

	i = 0;
	if (data->check_hd == 1)
	{
		data->hd_pipefd = malloc(sizeof(int *) * data->heredoc_nb);
		if (!data->hd_pipefd)
			return (0);
		while (i < data->heredoc_nb)
		{
			data->hd_pipefd[i] = malloc(sizeof(int) * 2);
			if (!data->hd_pipefd[i])
			{
				free_inttab(data->hd_pipefd, i);
				return (0);
			}
			if (pipe(data->hd_pipefd[i]) == -1)
			{
				perror("pipe");
				return (0);
			}
			i++;
		}
	}
	return (i);
}

int	check_for_append(t_shell *parse, int index)
{
	if (parse->tab_infile[index] == NULL)
		return (1);
	else if (parse->tab_infile[index]->type == 'C' && parse->tab_infile[index]->next == NULL)
		return (1);
	else if (parse->tab_infile[index]->type == 'A' && parse->tab_infile[index]->next == NULL)
		return (0);
	while (parse->tab_infile[index] != NULL)
	{
		if (parse->tab_infile[index]->type == 'A')
			return (0);
		parse->tab_infile[index] = parse->tab_infile[index]->next;
	}
	return (1);
}

int	heredoc_exec(t_data *data, t_shell *parse)
{
	int	i;
	int	index;
	int	ptr;
	int	pipe_nb;
	int	tmp;

	i = -1;
	index = 0;
	pipe_nb = hd_pipe_creation(data);
	(void)pipe_nb;
	data->hd_pid = malloc(sizeof(int) * data->heredoc_nb);
	if (!data->hd_pid)
		return (1);
	while (++i < data->heredoc_nb)
	{
		tmp = index;
		data->hd_pid[i] = fork();
		if (data->hd_pid[i] == -1)
		{
			ft_printf("Error while creating heredoc process\n");
			return (1);
		}
		while ((parse->tab_infile[index]->type != 'A') && (parse->tab_infile[index]->next != NULL))
			parse->tab_infile[index] = parse->tab_infile[index]->next;
		if (data->hd_pid[i] == 0)
			heredoc(data, parse, index);
		waitpid(data->hd_pid[i], &ptr, 0);
		if (ptr != 0)
			return (1);
		if (parse->tab_infile[index]->next != NULL)
			parse->tab_infile[index] = parse->tab_infile[index]->next;
		else if (parse->tab_infile[index]->next == NULL)
		{
			index++;
			while (check_for_append(parse, index) == 1 && (index != parse->infile_size + 1))
				index++;
		}
		data->hd_pipe_id++;
		data->hd_id++;
	}
	return (0);
}
//je passe a la ligne suivant que si elle est nul mdr