/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:11:11 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/09/19 13:28:19 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "cmd_exec/cmd_include/pipex_bonus.h"
#include <readline/readline.h>
#include <readline/history.h>

void	cmd_exec(t_data *data, char **envp, char **argv);

int		p_status = 0;

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_mini_data	mini_data;
	t_data		data;
	//(void)envp;
	// struct dirent *pdir;
	// DIR		*dir;

	// dir = NULL;
	// pdir = NULL;

	/*============================================================================*/
	mini_data.p_status = &p_status;
	mini_data.echo_sq_check = 0;
	p_status = 0;

	char	*input;
	int		envpsize = 0;
	int		(*builtins[7])(t_mini_data *data);
	int		builtin_cmd_nb = 7;
	
	char	*builtins_name[] = {
		"cd",
		"echo",
		"env",
		"pwd",
		"export",
		"unset",
		"exit"
	};

	builtins[0] = &mini_cd;			//OK + penser a enlever les printf
	builtins[1] = &mini_echo;		//OK
	builtins[2] = &mini_env;		//OK
	builtins[3] = &mini_pwd;		//OK mais probleme avec buff
	builtins[4] = &mini_export;		//OK + si PT$MDR=issou --> on export PT=issou + gerer plusieurs declaration
	builtins[5] = &mini_unset;		//OK
	builtins[6] = &mini_exit;		//OK mais à vérifier

	while (envp[envpsize])
		envpsize++;
	
	mini_data.name = "PTDR";
	mini_data.value = "issou";
	mini_data.path = "issou";
	mini_data.str = "$LOGN$AME on est $HOM$?E la $ISS$?OU hein cha$kal $TERM $?";//$LOGNAM on est $HOM$?E la $ISS$?OU hein cha$kal $TERM $?
	mini_data.echo_arg = 0;
	mini_data.var_name = "PTDR";
	mini_data.hd_limit = "on est la hein";
	mini_data.envp_size = envpsize;
	mini_data.env = envp;
	printf("ENVP SIZE BEGINING : %d\n", mini_data.envp_size);

	int	i;
	int	check;

	while (1)									//mini_data.env = envp; ou data->env dans les fonctions builitins
	{
		input = readline("minishell$ ");
		check = 0;
		i = 0;
		while (i < builtin_cmd_nb)
		{
			if (input)
			{
				if (ft_strcmp(builtins_name[i], input) == 0)
				{
					if ((*builtins[i])(&mini_data) == 1)
					{
						printf("P_STATUS fail : %d\n", *mini_data.p_status);
						check = 1;
						break ;
					}
					if (i == 4)
					{
						if (mini_data.unset_env)
							free_tab(mini_data.unset_env, mini_data.envp_size - 2);
						mini_data.env = mini_data.new_env;
					}
					if (i == 5)
					{
						if (mini_data.new_env)
							free_tab(mini_data.new_env, mini_data.envp_size);
						mini_data.env = mini_data.unset_env;
					}
					check = 1;
					break;
				}
			}
			i++;
		}
		if (check == 0)
			cmd_exec(&data, envp, argv);
		free(input);
	}
}
//pas oublier de free apres un appel a mini_env
//probleme avec export --> a chaque export, je creer un nouveau tableau que je peux pas free

void	cmd_exec(t_data *data, char **envp, char **argv)
{

	/* --- INIT DES VARIABLES D'EXECUTION ---*/
	data->envp_size = 0;
	while (envp[data->envp_size])
		data->envp_size++;
	
	data->input_fd = STDIN_FILENO;
	data->output_fd = STDOUT_FILENO;

	data->p_status = &p_status;

	data->hd_pipe_id = 0;
	data->hd_id = 0;

	data->cmd_nb = 3;
	data->heredoc_nb = 2;
	data->check_hd = 1;

	data->hd.delimiter_quotes = 0;
	data->envp = envp;

	data->exec.infile_fd = "infile.txt";
	data->exec.outfile_fd = "outfile.txt";
	data->exec.first_cmd_test = "/bin/cat -e";
	data->exec.last_cmd_test = "rev";

	data->exec.first_cmd_squotes_check = 0;
	data->exec.infile_check = 0;
	data->exec.outfile_check = 0;
	data->exec.last_cmd_outfile_check = 0;
	data->exec.pipe_check = 1;
	/* --- FIN DE L'INIT ---*/

	int pipe_nb = 0;
	int j = 0;
	int	ptr;
	if (data->heredoc_nb > 0)					//on s'occupe d'abord des Heredocs
	{
		heredoc_exec(data);
		while (j < data->heredoc_nb)			//on attend les process des HD
		{
			waitpid(data->hd_pid[j], &ptr, 0);
			j++;
		}
	}
	pipe_nb = pipe_creation(data);				//On cree les pipe
	if (data->cmd_nb > 0)						//En fonction du nombre de commande, on execute
	{
		first_command(envp, data);
		if (data->cmd_nb > 1)
		{
			commands(data, argv, envp);
			last_command(envp, data);
		}
	}
	if (data->hd_pipefd)						//on close les pipes des Heredocs
		close_hd_pipe(data, data->heredoc_nb - 1);
	if (data->exec.pipe_check > 0)				//on close les pipes des process
		close_pipe(data, (pipe_nb - 1));
	while (wait(NULL) != -1)					//on attend les process
		;
	//printf("p_status : %d === p_id : %d\n", *data->p_status, getpid());
	if (data->check_hd > 0)
		free(data->hd_pid);
	//free(data->home_path);
	return ;
}


//attention a la gestion d'erreur si j'unset des variables utiles a l'exec