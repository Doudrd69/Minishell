/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 17:44:13 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/18 14:29:46 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*main_init_check(t_data *data, t_shell *minishell, t_node *node)
{
	data->hd_id = 0;
	if (minishell->nbr_pipe > 0)
		data->pipe_check = 1;
	else
		data->pipe_check = 0;
	if (minishell->head != NULL)
		node = minishell->head;
	else
		node = NULL;
	if (minishell->tab_infile != NULL)
		data->infile_check = 1;
	else
		data->infile_check = 0;
	if (minishell->tab_outfile != NULL)
		data->outfile_check = 1;
	else
		data->outfile_check = 0;
	if (minishell->nbr_pipe > 0)
	{
		data->cmd_nb = minishell->nbr_pipe + 1;
		data->pipe_nb = pipe_creation(data, minishell->nbr_pipe);
	}
	else
		data->cmd_nb = 1;
	return (node);
}

void	sighandler_hd(int signum)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	exit(signum);
}

void	envp_check(t_data *data, char **envp)
{
	int	envpsize;

	envpsize = 0;
	if (envp[0] != NULL)
	{
		while (envp[envpsize])
			envpsize++;
		data->envp_size = envpsize;
	}
	else
	{
		if (export_no_env(data) == 1)
			exit(1);
		data->envp = data->no_env;
		envpsize = 3;
		data->envp_size = envpsize;
	}
	return ;
}

void	main_init_before_loop(t_data *data, char **envp,
	int (*builtins[7])(t_data *data, t_node *node), int argc, char *argv[])
{
	(void)argv;
	(void)argc;
	init_builtins_tab(data->builtins_name, builtins);
	init_main(data, envp);
	envp_check(data, envp);
	return ;
}

void	execution(t_data *data, t_shell *parse, t_node *node,
	int (*builtins[7])(t_data *, t_node *), int *gstatus)
{
	int	i;

	i = 0;
	data->check_main = 3;
	if (parse->cmd && *parse->cmd)
		add_history (parse->cmd);
	if (parsing(data->envp, parse) == 0)
	{
		data->hd_pipe_id = 0;
		node = main_init_check(data, parse, node);
		if (start_heredoc(data, parse, node) == 1)
			return ;
		while (i < data->heredoc_nb - 1)
			close(data->hd_pipefd[i++][WRITE]);
		if (parse->nbr_pipe == 0 && parse->tab_outfile == NULL)
		{
			data->check_main = builtins_loop(data->builtins_name, builtins,
					node, data, gstatus);
		}
		if (data->check_main == 3)
			cmd_exec(data, parse, builtins);
	}
	if (parse->synt_err == 1)
		data->p_status = parse->error;
	return ;
}
