/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:14:50 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/24 17:21:45 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_include/pipex_bonus.h"
#include "../includes/minishell.h"

void	sigtest(int signum)
{
	(void)signum;
	write(1, "Quit : 3\n", 9);
}

int	fork_creation(int pid)
{
	pid = fork();
	if (pid == -1)
	{
		ft_printf("Error : fork failed\n");
		exit(1);
	}
	return (pid);
}

int	check_pipe(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	*count_nb_of_args(t_node *node, t_data *data, int i)
{
	data->nb_of_args = 0;
	node = node->next;
	while(i < data->lst_size)
	{
		data->nb_of_args++;
		i++;
		if (node->next == NULL || ft_strncmp(node->next->content, "|", 4) == 0)
			break ;
		node = node->next;
	}
	while (--i >= 0)
		node = node->prev;
	return (node);
}

int	copy_args_in_param_tab(t_node *node, t_data *data, char **tab, int i, int j)
{
	if (data->nb_of_args > 0)
		node = node->next;
	while (i < data->nb_of_args && data->nb_of_args > 0)
	{
		tab[j] = malloc(sizeof(char) * ft_strlen(node->content) + 1);
		if (!tab[j])
		{
			free_tab(tab, j - 1);
			return (0);
		}
		ft_strlcpy(tab[j], node->content, ft_strlen(node->content), 1);
		node = node->next;
		j++;
		i++;
	}
	return (j);
}

char **fill_param_tab(t_node *node, t_data *data, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (node->next == NULL)
		data->nb_of_args = 0;
	else if (ft_strncmp(node->next->content, "|", 1) == 0 && node->next != NULL)
		data->nb_of_args = 0;
	else if ((ft_strncmp(node->next->content, "|", 1) != 0) || node->next != NULL)
		node = count_nb_of_args(node, data, i);
	else
		printf("Error : impossible to create PARAM TAB\n");
	tab = malloc(sizeof(char *) * (data->nb_of_args + 2));//cmd + NULL
	if (!tab)
		return (NULL);
	tab[0] = malloc(sizeof(char) * ft_strlen(node->content) + 1);
	if (!tab[0])
		return (free_tab(tab, 0));
	ft_strlcpy(tab[0], node->content, ft_strlen(node->content), 1);
	i = 0;
	j = copy_args_in_param_tab(node, data, tab, i, j);
	tab[j] = NULL;
	return (tab);
}

void	first_command(char *envp[], t_data *data, t_node *node)
{
	signal(SIGQUIT, &sigtest);
	data->first_cmd_pid = fork_creation(data->first_cmd_pid);
	if (data->first_cmd_pid == 0)
	{
		if (check_inputfile(data) != 0)
			return ;
		data->env.tab1 = get_path(envp, data, data->env.tab1);
		data->env.param_tab1 = fill_param_tab(node, data, data->env.param_tab1);
		check_outfile(data);
		first_cmd_execution(data, envp);
	}
}

void	last_command(char *envp[], t_data *data, t_node *node)
{
	data->last_cmd_pid = fork_creation(data->last_cmd_pid);
	if (data->last_cmd_pid == 0)
	{
		if (dup2(data->pipefd[data->cmd_nb - 2][READ], STDIN_FILENO) == -1)
		{
			perror("dup2");
			return ;
		}
		check_outfile_last_cmd(data);
		data->env.tab2 = get_path(envp, data, data->env.tab2);
		data->env.param_tab2 = fill_param_tab(node, data, data->env.param_tab2);
		last_cmd_execution(data, envp);
	}
}

void	commands(t_data *data, t_node *node, char *envp[])
{
	int	i;
	int	cmd_id;
	int	*pid;

	i = -1;
	cmd_id = 3;
	data->pipe_id = 1;
	pid = malloc(sizeof(int) * (data->cmd_nb - 2));
	if (!pid)
		return ;
	while (++i < (data->cmd_nb - 2))
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			ft_printf("Error while creating processes\n");
			return ;
		}
		if (pid[i] == 0)
			command_exec(data, node, envp, cmd_id);
		node = node->next->next;
		data->pipe_id++;
	}
	free(pid);
	return ;
}


//cat -e -n | grep e | rev marche pas