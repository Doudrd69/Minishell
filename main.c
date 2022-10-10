/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:11:11 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/10 15:04:06 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "cmd_exec/cmd_include/pipex_bonus.h"
#include <readline/readline.h>
#include <readline/history.h>

void	exec_main(t_data *data, char *envp[], char **argv);
int		export_exec(t_mini_data *mini_data, t_data *data);
void	cmd_exec(t_data *data, char **envp, char **argv);
int		unset_exec(t_mini_data *mini_data, t_data *data);
void	heredoc_main(t_data *data);

int		p_status = 0;

int	check_eof(char *str)
{
	if ((ft_strncmp(str, "test", 4) == 0))
	{
		if (check_delimiter(str, "test") == 0)
			return (0);
	}
	return (1);
}

void	eof_handler(char *input)//si dans HD, ou un sleep ---> attendre fin des processus? free?
{
	if (input == NULL)
	{
		write(2, "exit\n", 5);
		exit(0);
	}
	return ;
}

void	sighandler()
{
	write(2, "\n", 1);
	rl_replace_line("", 0);//on remplace le buffer de readline (rl_line_buffer)
	rl_on_new_line();
	rl_redisplay();
}
//rl_line_buffer = vide quand on C-c

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	//(void)argv;
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
	builtins[4] = &mini_export;		//OK (+ si PT$MDR=issou --> on export PT=issou (gestion dans le parsing) + gerer plusieurs declarations)
	builtins[5] = &mini_unset;		//OK
	builtins[6] = &mini_exit;		//A FAIRE

	while (envp[envpsize])
		envpsize++;
	
	mini_data.name = "SHELLISSOU";
	mini_data.value = "issou";
	mini_data.path = "..";
	mini_data.str = "$LOGNAME$HOME$USER$SHLVL$TERM \\$555USER";//$LOGNAM on est $HOM$?E la $ISS$?OU hein cha$kal $TERM $?
	mini_data.echo_arg = 0;
	mini_data.var_name = "PTDR";
	mini_data.hd_limit = "on est la hein";
	mini_data.envp_size = envpsize;
	mini_data.env = envp;
	data.envp = envp;
	//printf("ENVP SIZE BEGINING : %d\n", mini_data.envp_size);

	int	i;
	int	check;

	mini_data.unset_env_check = 0;
	mini_data.new_env_check = 0;
	signal(SIGINT, &sighandler);
	while (1)									//mini_data.env = envp; ou data->env dans les fonctions builitins
	{
		input = readline("minishell$ ");
		eof_handler(input);
		check = 0;
		i = 0;
		data.envp_size = mini_data.envp_size;
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
						export_exec(&mini_data, &data);
					if (i == 5)
						unset_exec(&mini_data, &data);
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

void	cmd_exec(t_data *data, char **envp, char **argv)
{

	/* --- INIT DES VARIABLES D'EXECUTION ---*/
	data->input_fd = STDIN_FILENO;
	data->output_fd = STDOUT_FILENO;

	data->p_status = &p_status;

	data->hd_pipe_id = 0;
	data->hd_id = 0;

	data->cmd_nb = 1;
	data->heredoc_nb = 1;
	data->check_hd = 1;

	data->hd.delimiter_quotes = 0;

	data->exec.infile_fd = "infile.txt";
	data->exec.outfile_fd = "outfile.txt";
	data->exec.first_cmd_test = "/bin/cat -e";
	data->exec.last_cmd_test = "rev";

	data->exec.first_cmd_squotes_check = 0;
	data->exec.infile_check = 0;
	data->exec.outfile_check = 0;
	data->exec.last_cmd_outfile_check = 0;
	data->exec.pipe_check = 0;
	/* --- FIN DE L'INIT ---*/

	int pipe_nb = 0;
	heredoc_main(data);							//exec des HD
	pipe_nb = pipe_creation(data);				//On cree les pipe
	exec_main(data, envp, argv);				//exec des commandes
	if (data->check_hd == 1)						//on close les pipes des Heredocs
	{
		close_hd_pipe(data, data->heredoc_nb - 1);
		free_inttab(data->hd_pipefd, data->heredoc_nb - 1);
	}
	if (data->exec.pipe_check > 0)				//on close les pipes des process
		close_pipe(data, (pipe_nb - 1));
	while (wait(NULL) != -1)					//on attend les process
		;
	if (data->check_hd > 0)
		free(data->hd_pid);
	return ;
}

//si UNSET --> pb quand j'essaye d'afficher la var unset dans un HD
//attention a la gestion d'erreur si j'unset des variables utiles a l'exec
//dans HD ---> CTRL-C retourne au prompt sans executer le HD
//dans echo je pete sur "$USER99999" par exemple ---> on se return rien car pas de var trouve