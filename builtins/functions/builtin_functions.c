/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 08:48:10 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/13 14:47:53 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mini_cd(t_data *data, t_node *node)
{
	data->oldpwd = getcwd(data->buff_oldpwd, BUF_SIZE);
	if (node->next == NULL && ft_strncmp(node->content, "cd", 2) == 0)
	{
		if (no_path(data) == 1)
			return (1);
	}
	else
	{
		if (path_exists(data, node) == 1)
			return (1);
	}
	if (update_pwd(data) == 1)
		return (1);
	if (update_old_pwd(data) == 1)
		return (1);
	return (0);
}

int	mini_pwd(t_data *data, t_node *node)
{
	(void)node;
	if (data->pipe_check == 0)
	{
		if (getcwd(data->buff, BUF_SIZE) == NULL)
		{
			data->p_status = 1;
			return (1);
		}
		ft_printf("%s\n", data->buff);
		data->p_status = 0;
		return (0);
	}
	return (2);
}

int	mini_env(t_data *data, t_node *node)
{
	int	i;
	int	j;

	i = 0;
	(void)node;
	if (data->pipe_check == 0)
	{
		if (data->envp[0] == NULL)
			return (1);
		while (i < data->envp_size)
		{
			j = 0;
			while (data->envp[i][j])
			{
				if (data->envp[i][j] == '=')
				{
					ft_printf("%s\n", data->envp[i]);
					break ;
				}
				j++;
			}
			i++;
		}
		data->p_status = 0;
		return (0);
	}
	return (2);
}

int	mini_echo(t_data *data, t_node *node)
{
	int	i;
	int	check;
	int	loop;
	int	output_fd;

	loop = 0;
	output_fd = 1;
	data->echo_arg = 0;
	if (no_args(node) == 0)
		return (0);
	// printf("CMD_NB >> %d\n", data->cmd_nb);
	// if (data->outfile_check == 1 && data->cmd_nb == 1)
	// {
	// 	output_fd = open("lol.txt", O_RDONLY | O_CREAT, 0666);
	// 	if (output_fd < 0)
	// 	{
	// 		ft_printf("minishell: %s: %s\n", data->echo_file, strerror(errno));
	// 		return (1);
	// 	}
	// 	if (dup2(output_fd, STDIN_FILENO) == -1)
	// 	{
	// 		perror("dup2");
	// 		return (1);
	// 	}
	// }
	// else
	// 	output_fd = 1;
	// printf("OUTPUT FD --> %d\n", output_fd);
	if (data->pipe_check == 0 && data->outfile_check == 0)
	{
		printf("** In ECHO -- first node ==> %s **\n", node->content);
		while (node != NULL && node->type != 'P')
		{
			i = 0;
			check = 0;
			data->str = node->content;
			node = echo_arg_newline_check(data, node, check, loop);
			if (node == NULL)
				return (0);
			loop = 1;
			i = write_and_check_signs(i, data, output_fd);
			if (node->next != NULL && node->next->type != 'P')
				write(output_fd, " ", 1);
			node = node->next;
		}
		// if (data->outfile_check == 1)
		// 	close(output_fd);
		return (newline_arg(data, output_fd));
	}
	return (2);
}

int	mini_exit(t_data *data, t_node *node)
{
	int	tmp;

	tmp = ft_atoi(node->content);
	if (data->pipe_check == 0)
	{
		data->p_status = tmp;
		exit((unsigned char)tmp);
	}
	return (2);
}

//echo seul et sans redirection				--> fonction builtin			OK
//echo seul et avec redirection				--> fonction builtin			OK
//echo seul avec -n et sans redirection		--> fonction builtin			OK
//echo seul avec -n et avec redirection		--> fonction builtin			/!\ ecriture des -n

//echo avec commandes et sans redirection	--> exec						OK
//echo avce commandes et avec redirection	--> exec						OK
//echo avec commandes -n et sans redirection		--> ?					/!\ ecriture des -n
//echo avec commandes -n et avec redirection		--> ?					/!\ ecriture des -n