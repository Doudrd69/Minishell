/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:44:04 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/17 13:47:48 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../parsing/parsing.h"

void	init_main(t_data *data, char **envp)
{
	data->var_export = NULL;
	data->str = NULL;
	data->unset_env_check = 0;
	data->builtin_cmd_nb = 7;
	data->first_cd_check = 0;
	data->new_env_check = 0;
	data->outfile_check = 0;
	data->echo_sq_check = 0;
	data->infile_check = 0;
	data->check_main = 3;
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
	data->hd_id = 0;
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

void	init_builtins_tab(char *builtins_name[7],
	int (*builtins[7])(t_data *, t_node *))
{
	builtins_name[0] = "cd";
	builtins_name[1] = "echo";
	builtins_name[2] = "env";
	builtins_name[3] = "pwd";
	builtins_name[4] = "exit";
	builtins_name[5] = "export";
	builtins_name[6] = "unset";
	builtins[0] = &mini_cd;
	builtins[1] = &mini_echo;
	builtins[2] = &mini_env;
	builtins[3] = &mini_pwd;
	builtins[4] = &mini_exit;
	builtins[5] = &export_exec;
	builtins[6] = &unset_exec;
	return ;
}
