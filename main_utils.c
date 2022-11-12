/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:44:04 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/12 12:13:41 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "parsing/parsing.h"
#include "cmd_exec/cmd_include/pipex_bonus.h"

static int	test_free(void *tmp)
{
	if (tmp == NULL)
		return (0);
	else
		free(tmp);
	return (1);
}

void	free_all(t_shell *minishell)
{
	t_node	*tmp;

	while (minishell->head && minishell->head != NULL)
	{
		tmp = minishell->head;
		minishell->head = minishell->head->next;
		if (ft_strncmp(tmp->content, "|", 1) != 0)
			test_free((void *)(tmp->content));
		test_free((void *)(tmp));
	}
	test_free((void *)(minishell->value));
	test_free((void *)(minishell->var_search));
	test_free((void *)(minishell->home_path));
	free(minishell);
}

void	init_main(t_mini_data *mini_data, t_data *data, char **envp)
{
	mini_data->var_export = NULL;
	mini_data->str = NULL;
	mini_data->unset_env_check = 0;
	mini_data->first_cd_check = 0;
	mini_data->new_env_check = 0;
	mini_data->echo_sq_check = 0;
	mini_data->infile_check = 0;
	mini_data->outfile_check = 0;
	mini_data->oldpwd_if = 0;
	mini_data->echo_arg = 0;
	mini_data->env = envp;
	data->envp = envp;
	data->p_status = &mini_data->p_status;
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
	data->heredoc_nb = 0;						//ca va degager apres implementation
	data->exec.last_cmd_outfile_check = 0;		//ca va degager apres implementation
	if (data->cmd_nb > 1)
		data->exec.pipe_check = 1;
	else
		data->exec.pipe_check = 0;
	return ;
}

void	init_builtins_tab(char *builtins_name[5], int (*builtins[5])(t_mini_data *, t_node *))
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
	// printf("PTAB1  size : %d --> %p\n", data->size_ptab1, data->env.param_tab1);
	// printf("PTAB2  size : %d --> %p\n", data->size_ptab2, data->env.param_tab2);
	// printf("PTAB3  size : %d --> %p\n", data->size_ptab3, data->env.param_tab3);
	if (data->env.param_tab1 != NULL)
		free_tab(data->env.param_tab1, data->size_ptab1 - 1);
	if (data->env.param_tab2 != NULL)
		free_tab(data->env.param_tab2, data->size_ptab2 - 1);
	if (data->env.param_tab3 != NULL)
		free_tab(data->env.param_tab3, data->size_ptab3 - 1);
	return ;
}
