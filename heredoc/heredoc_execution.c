/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 10:04:20 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/07 19:19:42 by ebrodeur         ###   ########lyon.fr   */
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

int	check_for_append(t_node *infile_tmp)
{
	if (infile_tmp == NULL)
		return (1);
	else if (infile_tmp->type == 'C' && infile_tmp->next == NULL)
		return (1);
	else if (infile_tmp->type == 'A' && infile_tmp->next == NULL)
		return (0);
	while (infile_tmp->next != NULL)
	{
		if (infile_tmp->type == 'A')
			return (0);
		infile_tmp = infile_tmp->next;
	}
	return (1);
}

int	heredoc_exec(t_data *data, t_node **infile_tmp, t_shell *parse)
{
	int	i;
	int	index;
	int	ptr;
	int	pipe_nb;
	t_node *tmp;

	i = -1;
	index = 0;
	(void)pipe_nb;
	pipe_nb = hd_pipe_creation(data);
	data->hd_pid = malloc(sizeof(int) * data->heredoc_nb);
	if (!data->hd_pid)
		return (1);
	tmp = infile_tmp[index];
	while (++i < data->heredoc_nb)
	{
		data->hd_pid[i] = fork();
		if (data->hd_pid[i] == -1)
		{
			ft_printf("Error while creating heredoc process\n");
			return (1);
		}
		while ((tmp->type != 'A') && (tmp->next != NULL))
			tmp = tmp->next;
		if (data->hd_pid[i] == 0)
			heredoc(data, tmp);
		waitpid(data->hd_pid[i], &ptr, 0);
		if (ptr != 0)
			return (1);
		if (tmp->next != NULL)
			tmp = tmp->next;
		if (tmp->next == NULL)
		{
			index++;
			tmp = infile_tmp[index];
			while (check_for_append(tmp) == 1 && (index != parse->infile_size + 1))
			{
				index++;
				tmp = infile_tmp[index];
			}
		}
		tmp = infile_tmp[index];
		data->hd_pipe_id++;
		data->hd_id++;
	}
	dprintf(2, "INDEX ==> %d\n", index);
	return (0);
}
//attention "<<a < main.c cat | <<s <<d cat | rev | rev | rev | rev | <<f grep e > lol.txt" --> je saute le <<d et segfault apres le <<f