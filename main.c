/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:11:11 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/24 18:08:45 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "parsing/parsing.h"
#include "cmd_exec/cmd_include/pipex_bonus.h"
#include <readline/readline.h>
#include <readline/history.h>

int		export_exec(t_mini_data *mini_data, t_data *data, t_node *node);
int		unset_exec(t_mini_data *mini_data, t_data *data, t_node *node);
void	cmd_exec(t_data *data, char **envp, t_shell *minishell);
void	exec_main(t_data *data, char *envp[], t_node *node);
void	heredoc_main(t_data *data);

int		p_status;

void	free_all(t_shell *minishell)
{
	t_node	*tmp;

	while (minishell->head && minishell->head != NULL)
	{
		tmp = minishell->head;
		minishell->head = minishell->head->next;
		if (ft_strncmp(tmp->content, "|", 1) != 0)
			free(tmp->content);
		free(tmp);
	}
	free(minishell->value);
	free(minishell->var_search);
	free(minishell);
}

void	sighandler_hd(int signum)
{
	(void)signum;
	p_status = 1;
	exit(1);
	//si plusieurs HD, on quitte TOUT
	//mini_exit(2);
}

void	init_main(t_mini_data *mini_data, t_data *data, char **envp)
{
	mini_data->name = "TEST";		//on recup ca dans le parsing
	mini_data->value = "issou";
	mini_data->var_export = NULL;
	mini_data->path = "..";
	mini_data->str = NULL;
	mini_data->echo_arg = 0;
	mini_data->var_name = "";
	mini_data->hd_limit = "on est la hein";
	mini_data->env = envp;
	mini_data->no_env_check = 0;	//utils epour la creation du oldpwd
	mini_data->first_cd_check = 0;
	mini_data->unset_env_check = 0;
	mini_data->new_env_check = 0;
	mini_data->p_status = &p_status;
	mini_data->echo_sq_check = 0;
	mini_data->oldpwd_if = 0;
	data->envp = envp;
	p_status = 0;
	return ;
}

void	cmd_exec_init(t_data *data, t_shell *parse_data)
{
	data->input_fd = STDIN_FILENO;
	data->output_fd = STDOUT_FILENO;
	data->env.param_tab1 = NULL;
	data->env.param_tab2 = NULL;
	data->env.param_tab3 = NULL;

	data->lst_size = parse_data->list_size;

	data->p_status = &p_status;

	data->hd_pipe_id = 0;
	data->hd_id = 0;

	data->cmd_nb = parse_data->nbr_pipe + 1;
	data->heredoc_nb = 0;
	data->check_hd = 0;

	data->hd.delimiter_quotes = 0;

	data->exec.infile_fd = "infile.txt";
	data->exec.outfile_fd = "outfile.txt";
	data->exec.first_cmd_test = "cat -e";
	data->exec.last_cmd_test = "rev";

	data->exec.first_cmd_squotes_check = 0;
	data->exec.infile_check = 0;
	data->exec.outfile_check = 0;
	data->exec.last_cmd_outfile_check = 0;
	if (data->cmd_nb > 1)
		data->exec.pipe_check = 1;
	else
		data->exec.pipe_check = 0;
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

int main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	struct		sigaction sa;
	t_mini_data	mini_data;
	t_data		data;
	t_shell		*minishell;
	t_node		*node;
	int			builtin_cmd_nb = 5;
	int			envpsize = 0;
	int			check;
	int			i;
	int			(*builtins[5])(t_mini_data *data, t_node *node);
	char		*builtins_name[] = {
		"cd",
		"echo",
		"env",
		"pwd",
		"exit",
	};

	builtins[0] = &mini_cd;			//OK + penser a enlever les printf
	builtins[1] = &mini_echo;		//OK
	builtins[2] = &mini_env;		//OK
	builtins[3] = &mini_pwd;		//OK mais probleme avec buff
	builtins[4] = &mini_exit;		//A FAIRE

	init_main(&mini_data, &data, envp);
	sa.sa_handler = SIG_IGN;
	envp_check(&mini_data, &data, envp, envpsize);
	while (1)
	{
		signal(SIGINT, &sighandler);
		sigaction(SIGQUIT, &sa, NULL);
		minishell = malloc(sizeof(t_shell));
		init_variable(minishell, data.envp_size, data.envp);
		minishell->cmd = readline("minishell$ ");
		if (minishell->cmd && *minishell->cmd)
			add_history (minishell->cmd);
		eof_handler(minishell->cmd, minishell);
		parsing(data.envp, minishell);
		node = minishell->head;
		print_dlist(&node, minishell);
		// printf("PIPE NUMBER = %d\n", minishell->nbr_pipe);
		check = 0;
		data.envp_size = mini_data.envp_size;
		i = 0;
		while (i < builtin_cmd_nb)
		{
			if (ft_strncmp(builtins_name[i], node->content, ft_strlen(node->content)) == 0)
			{
				//printf("CMD : %s*\n", node->content);
				if (node->next != NULL)
					node = node->next;
				if ((*builtins[i])(&mini_data, node) == 1)
				{
					printf("P_STATUS fail : %d\n", *mini_data.p_status);
					check = 1;
					break ;
				}
				check = 1;
				break;
			}
			i++;
		}
		if (ft_strncmp(node->content, "export", 6) == 0)
		{
			export_exec(&mini_data, &data, node);
			check = 1;
		}
		if (ft_strncmp(node->content, "unset", 5) == 0)
		{
			unset_exec(&mini_data, &data, node);
			check = 1;
		}
		if (check == 0)
			cmd_exec(&data, data.envp, minishell);
		free(minishell->cmd);
		free_all(minishell);
	}
}

void	cmd_exec(t_data *data, char **envp, t_shell *minishell)
{
	t_node *node;

	node = minishell->head;//la on est sur la commande
	cmd_exec_init(data, minishell);
	int pipe_nb = 0;
	heredoc_main(data);							//exec des HD
	pipe_nb = pipe_creation(data);				//On cree les pipe + il me faut le nombre de cmd la dedans
	exec_main(data, envp, node);				//exec des commandes
	if (data->check_hd == 1)					//on close les pipes des Heredocs
	{
		close_hd_pipe(data, data->heredoc_nb - 1);
		free_inttab(data->hd_pipefd, data->heredoc_nb - 1);
	}
	if (data->exec.pipe_check > 0)				//on close les pipes des process
		close_pipe(data, (pipe_nb - 1));
	while (wait(NULL) != -1)					//on attend les process
		;
	if (data->env.param_tab1 != NULL)
		free_tab(data->env.param_tab1, 3);
	if (data->env.param_tab2 != NULL)
		free_tab(data->env.param_tab2, 3);
	if (data->env.param_tab3 != NULL)
		free_tab(data->env.param_tab3, 3);
	if (data->check_hd > 0)
		free(data->hd_pid);
	return ;
}
//dans HD ---> CTRL-C retourne au prompt sans executer le HD
//demander le parsing du export
//le exit va casser les couilles