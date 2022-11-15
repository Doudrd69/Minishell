/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:44:04 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/15 10:13:39 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../parsing/parsing.h"

void	free_all(t_shell *minishell)
{
	t_node	*tmp;

	while (minishell->head && minishell->head != NULL)
	{
		tmp = minishell->head;
		minishell->head = minishell->head->next;
		test_free((void *)(tmp));
	}
	test_free((void *)(minishell->value));
	test_free((void *)(minishell->var_search));
	test_free((void *)(minishell->home_path));
	free(minishell);
}

void	init_main(t_data *data, char **envp)
{
	data->var_export = NULL;
	data->str = NULL;
	data->unset_env_check = 0;
	data->builtin_cmd_nb = 5;
	data->first_cd_check = 0;
	data->new_env_check = 0;
	data->outfile_check = 0;
	data->echo_sq_check = 0;
	data->infile_check = 0;
	data->check_main = 0;
	data->oldpwd_if = 0;
	data->echo_arg = 0;
	data->p_status = 0;
	data->envp = envp;
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
	data->hd_pipe_id = 0;
	data->hd_id = 0;
	if (parse_data->nbr_appendin > 0)
		data->check_hd = 1;
	else
		data->check_hd = 0;
	data->cmd_nb = parse_data->nbr_pipe + 1;
	data->size_ptab1 = 0;
	data->size_ptab2 = 0;
	data->size_ptab3 = 0;
	data->heredoc_nb = 0;
	data->exec.last_cmd_outfile_check = 0;
	if (data->cmd_nb > 1)
		data->exec.pipe_check = 1;
	else
		data->exec.pipe_check = 0;
	return ;
}

void	init_builtins_tab(char *builtins_name[5],
	int (*builtins[5])(t_data *, t_node *))
{
	builtins_name[0] = "cd";
	builtins_name[1] = "echo";
	builtins_name[2] = "env";
	builtins_name[3] = "pwd";
	builtins_name[4] = "exit";
	builtins[0] = &mini_cd;
	builtins[1] = &mini_echo;
	builtins[2] = &mini_env;
	builtins[3] = &mini_pwd;
	builtins[4] = &mini_exit;
	return ;
}

void	free_param_tab(t_data *data)
{
	if (data->env.param_tab1 != NULL)
		free_tab(data->env.param_tab1, data->size_ptab1 - 1);
	if (data->env.param_tab2 != NULL)
		free_tab(data->env.param_tab2, data->size_ptab2 - 1);
	if (data->env.param_tab3 != NULL)
		free_tab(data->env.param_tab3, data->size_ptab3 - 1);
	return ;
}
