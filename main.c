/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:11:11 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/03 15:04:07 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "parsing/parsing.h"
#include "cmd_exec/cmd_include/pipex_bonus.h"
#include <readline/readline.h>
#include <readline/history.h>

void	exec_main(t_data *data, char *envp[], t_node *node, t_shell *parse);
void	init_main(t_mini_data *mini_data, t_data *data, char **envp);
void	cmd_exec(t_data *data, char **envp, t_shell *minishell);
void	cmd_exec_init(t_data *data, t_shell *parse_data);
void	heredoc_main(t_data *data, t_shell *parse);

int		export_exec(t_mini_data *mini_data, t_data *data, t_node *node);
int		unset_exec(t_mini_data *mini_data, t_data *data, t_node *node);

int		p_status;

void	sighandler_hd(int signum)
{
	(void)signum;
	p_status = 1;
	return ;
}

void	envp_check(t_mini_data *mini_data, t_data *data, char **envp, int envpsize)
{
	if (envp[0] != NULL)
	{
		while (envp[envpsize])
			envpsize++;
		mini_data->envp_size = envpsize;
		data->envp_size = envpsize;
	}
	else
	{
		if (export_no_env(mini_data) == 1)
			exit(1);
		envp = mini_data->no_env;
		mini_data->env = envp;
		data->envp = envp;
		envpsize = 3;
		mini_data->envp_size = envpsize;
		data->envp_size = envpsize;
	}
	return ;
}

int		export_and_unset(t_mini_data *mini_data, t_data *data, t_node *node, int check)
{
	if (ft_strncmp(node->content, "export", 6) == 0)
	{
			export_exec(mini_data, data, node);
			return (1);
	}
	if (ft_strncmp(node->content, "unset", 5) == 0)
	{
		unset_exec(mini_data, data, node);
			return (1);
	}
	return (check);
}

int	builtins_loop(char *tab_name[5], int (*builtins[5])(t_mini_data *, t_node *), t_node *node, t_mini_data *data, int builtin_cmd_nb, int check)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < builtin_cmd_nb)
	{
		if (ft_strncmp(tab_name[i], node->content, ft_strlen(node->content)) == 0)
		{
			if (node->next != NULL)
				node = node->next;
			status = (*builtins[i])(data, node);
			if (status == 1)
			{
				printf("P_STATUS fail : %d\n", status);
				*data->p_status = status;
				return (1);
			}
			if (status == 2)
				return (check = 0);
			return (check = 1);
		}
		i++;
	}
	return (check);
}

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	struct sigaction	sa;
	t_mini_data			mini_data;
	t_data				data;
	t_shell				*minishell;
	t_node				*node;
	int					builtin_cmd_nb;
	int					envpsize;
	int					check;
	char				*builtins_name[5];
	int					(*builtins[5])(t_mini_data *data, t_node *node);

	envpsize = 0;
	builtin_cmd_nb = 5;
	mini_data.p_status = &p_status;
	data.p_status = &p_status;
	init_builtins_tab(builtins_name, builtins);
	sa.sa_handler = SIG_IGN;
	init_main(&mini_data, &data, envp);
	envp_check(&mini_data, &data, envp, envpsize);
	while (1)
	{
		sigaction(SIGQUIT, &sa, NULL);
		signal(SIGINT, &sigint_handler_main_loop);
		minishell = malloc(sizeof(t_shell));
		init_variable(minishell, data.envp_size, data.envp);
		minishell->cmd = readline("minishell$ ");
		eof_handler(minishell->cmd, minishell);
		if (ft_strncmp(rl_line_buffer, "\0", 1) != 0)
		{
			if (minishell->cmd && *minishell->cmd)
				add_history (minishell->cmd);
			parsing(data.envp, minishell);
			if (minishell->nbr_pipe > 0)
				mini_data.pipe_check = 1;
			else
				mini_data.pipe_check = 0;
			node = minishell->head;
			data.envp_size = mini_data.envp_size;
			check = 0;
			check = builtins_loop(builtins_name, builtins, node, &mini_data, builtin_cmd_nb, check);
			check = export_and_unset(&mini_data, &data, node, check);
			if (check == 0)
				cmd_exec(&data, data.envp, minishell);
		}
		if (data.exec.infile_fd)
			free(data.exec.infile_fd);
		free(minishell->cmd);
		free_all(minishell);
	}
}

void	cmd_exec(t_data *data, char **envp, t_shell *parse)
{
	t_node	*node;

	node = parse->head;
	cmd_exec_init(data, parse);
	int pipe_nb = 0;
	heredoc_main(data, parse);
	pipe_nb = pipe_creation(data);
	while (node->next != NULL)
		node = node->next;
	*data->p_status = ft_atoi(node->content);
	node = parse->head;
	exec_main(data, envp, node, parse);
	if (data->check_hd == 1)
	{
		close_hd_pipe(data, data->heredoc_nb - 1);
		free_inttab(data->hd_pipefd, data->heredoc_nb - 1);
	}
	if (data->exec.pipe_check > 0)
		close_pipe(data, (pipe_nb - 1));
	while (wait(NULL) != -1)
		;
	free_param_tab(data);
	if (data->check_hd > 0)
		free(data->hd_pid);
	return ;
}

//PARSING WILLIAM
	//pas le bon output --> echo $USER $123456789USER $USER123456789
	//echo '' "" ne devrait rien afficher
	//echo peut pas afficher plusieurs var d'affilées
	//probleme avec quotes --> les quotes sont affichées
	//sur l'export --> export LOL= on est la hein ==> LOL=on
	//echo "                          5                     " doit print tout les espaces

//MES TACHES
	//faire la verification de la secu des malloc
	//si "command not found" --> exit(127) et mettre p_status à 127
	//CTRL-C fonctionnel dans les Heredoc

	//implementation redirections
		//verif des outfiles
		//"< heredoc/heredoc.c grep if | cat -n" fait juste un cat -n --> faut gerer les conditions dans les fonctions inputfile
		//si plusieurs infiles (HD et Files) --> on va toujours prendre et executer le DERNIER
		//gerer les grands nombres pour exit (< 255 je crois)
		//"< main.c <<q < no_env.c <<w cat | <<e rev" --> la derniere commande n'a pas l.air de lire dans le bon stdin?