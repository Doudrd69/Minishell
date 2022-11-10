/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:11:11 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/10 16:09:26 by ebrodeur         ###   ########lyon.fr   */
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

int		heredoc_main(t_data *data, t_node ***intab, t_shell *parse);
int		export_exec(t_mini_data *mini_data, t_data *data, t_node *node);
int		unset_exec(t_mini_data *mini_data, t_data *data, t_node *node);

int		p_status;

void	sighandler_hd(int signum)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(signum);
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
	if (node && ft_strncmp(node->content, "export", 6) == 0)
	{
		if (node->next == NULL || node->next->type == 'P')
			return (display_export(mini_data));
		mini_data->p_status = export_exec(mini_data, data, node);
		return (1);
	}
	if (node && ft_strncmp(node->content, "unset", 5) == 0)
	{
		mini_data->p_status = unset_exec(mini_data, data, node);
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
	while (node && i < builtin_cmd_nb)
	{
		if (ft_strncmp(tab_name[i], node->content, ft_strlen(node->content)) == 0)
		{
			if (node->next != NULL)
				node = node->next;
			data->p_status = (*builtins[i])(data, node);
			if (data->p_status == 1)
			{
				printf("Error code debug : %d\n", data->p_status);
				return (1);
			}
			if (data->p_status == 2)
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
			if (minishell->head != NULL)
				node = minishell->head;
			else
				node = NULL;
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
	int		status;

	node = parse->head;
	cmd_exec_init(data, parse);
	int pipe_nb = 0;
	if (start_heredoc(data, parse) == 1)
		return ;
	if (node == NULL && parse->tab_outfile == NULL)
		return ;
	pipe_nb = pipe_creation(data);
	node = node_rotation_exec(node, parse);
	exec_main(data, envp, node, parse);
	if (data->check_hd == 1)
		close_hd_pipe(data, parse->nbr_appendin - 1);
	if (data->exec.pipe_check > 0)
		close_pipe(data, (pipe_nb - 1));
	while (wait(&status) != -1)
		;
	*data->p_status = set_p_status(status, data, node);
	free_param_tab(data);
	if (data->check_hd > 0)
		free(data->hd_pid);
	return ;
}

//MES TACHES
	//faire la verification de la secu des malloc
	//SIGINT dans le main (sans rien) --> error 1

	//si export abd --> on l'affiche pas dans env mais dans export
	//si export qwe= -> onl'affiche dans env et export
	//pb dans parsing --> single quote = boucle infinie