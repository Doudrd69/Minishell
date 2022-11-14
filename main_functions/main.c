/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 11:11:11 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 13:09:51 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../parsing/parsing.h"
#include <readline/readline.h>
#include <readline/history.h>

int		g_pstatus;

void	sigint_handler_main_loop(int signum)
{
	if (signum == 2)
	{
		g_pstatus = 1;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	export_and_unset(t_data *data, t_node *node, int check)
{
	if (node && ft_strncmp(node->content, "export", 6) == 0)
	{
		if (node->next == NULL || node->next->type == 'P')
			return (display_export(data));
		data->p_status = export_exec(data, node);
		return (1);
	}
	if (node && ft_strncmp(node->content, "unset", 5) == 0)
	{
		data->p_status = unset_exec(data, node);
		return (1);
	}
	return (check);
}

int	builtins_loop(char *tab_name[5], int (*builtins[5])(t_data *, t_node *),
	t_node *node, t_data *data, int *gstatus)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	printf("IN BUILTINS --> %d\n", *gstatus);
	data->test = &g_pstatus;
	while (node && i < data->builtin_cmd_nb)
	{
		if (ft_strncmp(tab_name[i], node->content,
				ft_strlen(node->content)) == 0)
		{
			if (node->next != NULL)
				node = node->next;
			data->p_status = (*builtins[i])(data, node);
			if (data->p_status == 1)
				return (1);
			if (data->p_status == 2)
				return (data->check_main = 0);
			return (data->check_main = 1);
		}
		i++;
	}
	return (data->check_main);
}

int	main(int argc, char *argv[], char *envp[])
{
	struct sigaction	sa;
	t_data				data;
	t_shell				*minishell;
	t_node				*node;
	int					(*builtins[5])(t_data *data, t_node *node);

	sa.sa_handler = SIG_IGN;
	main_init_before_loop(&data, envp, builtins, argc, argv);
	while (1)
	{
		g_pstatus = 0;
		sigaction(SIGQUIT, &sa, NULL);
		signal(SIGINT, &sigint_handler_main_loop);
		minishell = malloc(sizeof(t_shell));
		init_variable(minishell, data.envp_size, data.envp);
		minishell->cmd = readline("minishell$ ");
		eof_handler(minishell->cmd, minishell);
		node = NULL;
		if (ft_strncmp(rl_line_buffer, "\0", 1) != 0)
			execution(&data, minishell, node, builtins, &g_pstatus);
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
	if (start_heredoc(data, parse) == 1)
		return ;
	if (node == NULL && parse->tab_outfile == NULL)
		return ;
	node = node_rotation_exec(node, parse);
	exec_main(data, envp, node, parse);
	if (data->check_hd == 1)
		close_hd_pipe(data, parse->nbr_appendin - 1);
	if (data->exec.pipe_check > 0)
		close_pipe(data, (data->pipe_nb - 1));
	while (wait(&status) != -1)
		;
	data->p_status = set_p_status(status, node);
	free_param_tab(data);
	if (data->check_hd > 0)
		free(data->hd_pid);
	return ;
}
