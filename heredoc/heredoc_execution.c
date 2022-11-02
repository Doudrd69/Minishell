/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:04:20 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/02 16:58:24 by ebrodeur         ###   ########lyon.fr   */
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

int	heredoc_exec(t_data *data, t_shell *parse)
{
	int	i;
	int	index;
	int	ptr;
	int	pipe_nb;
	int	tmp = 0;

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
			printf("Error while creating heredoc process\n");
			return (1);
		}
		while ((parse->tab_infile[index]->type != 'A') && (parse->tab_infile[index]->next != NULL))
			parse->tab_infile[index] = parse->tab_infile[index]->next;
		printf("LIMITER ----> %s\n", parse->tab_infile[index]->content);
		if (data->hd_pid[i] == 0)
			heredoc(data, parse, index);
		waitpid(data->hd_pid[i], &ptr, 0);
		if (parse->tab_infile[index]->next == NULL)
			index++;
		if (parse->tab_infile[index] != NULL && tmp == index)
			parse->tab_infile[index] = parse->tab_infile[index]->next;
		if (parse->tab_infile[index] != NULL && tmp != index)
			;
		data->hd_pipe_id++;
		data->hd_id++;
	}
	return (0);
}

//pb j'affiche le limiter
//a chaque tour --> tant que j'ai de trucs sur ma ligne on continue --> puis on incremente (nouvelle ligne si existe)
//on reprend du debut de la liste