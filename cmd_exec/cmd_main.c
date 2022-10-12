/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:14:50 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/07 11:19:06 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cmd_include/pipex_bonus.h"
#include "../includes/minishell.h"

void	sigtest()
{
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

void	first_command(char *envp[], t_data *data)
{
	signal(SIGQUIT, &sigtest);
	data->first_cmd_pid = fork_creation(data->first_cmd_pid);
	if (data->first_cmd_pid == 0)
	{
		if (check_inputfile(data) != 0)
			return ;
		data->index = 2;//ici on fera correcpondre le bon ID du bon bloc de la liste chainee
		data->env.tab1 = get_path(envp, data, data->env.tab1);//remplacer par getenv + je recup ici un tableau 2d avec tout mes chemins d'exec
		data->env.param_tab1 = ft_split(data->exec.first_cmd_test, ' ');//on split la commande pour distinguer la cmd et ses arguments (ls -la)
		check_outfile(data);
		first_cmd_execution(data, envp);
	}
}

void	last_command(char *envp[], t_data *data)
{
	data->last_cmd_pid = fork_creation(data->last_cmd_pid);
	if (data->last_cmd_pid == 0)
	{
		if (dup2(data->pipefd[data->cmd_nb - 2][READ], STDIN_FILENO) == -1)//modifier l'id du pipe
		{
			perror("dup2");
			return ;
		}
		check_outfile_last_cmd(data);
		data->env.tab2 = get_path(envp, data, data->env.tab2);
		data->env.param_tab2 = ft_split(data->exec.last_cmd_test, ' ');
		last_cmd_execution(data, envp);
	}
}

void	commands(t_data *data, char *argv[], char *envp[])//que si plusieurs commandes (PIPE)
{
	int	i;
	int	cmd_id;
	int	*pid;
	(void)argv;

	i = 0;
	cmd_id = 3;
	data->pipe_id = 1;
	pid = malloc(sizeof(int) * (data->cmd_nb - 2));//soustraire le nb de heredoc
	if (!pid)
		return ;
	while (i < (data->cmd_nb - 2))
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			ft_printf("Error while creating processes\n");
			return ;
		}
		if (pid[i] == 0)
			command_exec(data, envp, cmd_id);
		data->pipe_id++;
		cmd_id++;
		i++;
	}
	free(pid);
	return ;
}

// int	main(int argc, char *argv[], char *envp[])
// {
//  	t_data	data;
// // 	int		i;

// // 	i = 0;
// // 	data.cmd_nb = argc - 3;
// // 	i = pipe_creation(&data);
// 	first_command(argv, envp, &data);
// // 	commands(&data, argv, envp);
// // 	last_command(argv, envp, argc, &data);
// // 	close_pipe(&data, (i - 1));
// 	while (wait(NULL) != -1)
// 		;
// }


//exemple :
	//ls -la | cat -e > outfile