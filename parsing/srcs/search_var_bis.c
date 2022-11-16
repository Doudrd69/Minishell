/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:53:02 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 20:19:31 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	var_exists_parsing(t_shell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->env_size)
	{
		if (ft_strnstr(minishell->envp[i], minishell->var_search,
				ft_strlen(minishell->var_search)))
		{
			if (check_var_parsing(minishell->envp[i], minishell->var_search))
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_var_parsing(char *str, char *var_name)
{
	size_t	size;

	size = 0;
	while (str[size] != '=')
		size++;
	if (size == ft_strlen(var_name))
		return (1);
	return (0);
}

void	copy_value_parsing(t_shell *minishell, int j, int i, char *var)
{
	i = 0;
	while (var[j] != ' ' && var[j] != '\0')
	{
		minishell->value[i] = var[j];
		j++;
		i++;
	}
	minishell->value[i] = '\0';
	return ;
}

int	check_and_print_var_parsing(t_shell *minishell, char *str)
{
	int		size;
	int		i;
	int		j;
	char	*position;

	j = 0;
	size = 0;
	i = 0;
	position = &str[0];
	find_position_of_dollars(position, i, &size);
	i = 1;
	minishell->var_search = malloc(sizeof(char) * size);
	if (!(minishell->var_search))
		return (1);
	while (i < size)
	{
		if (str[i] == '$' && i != 0)
			break ;
		minishell->var_search[j] = str[i];
		i++;
		j++;
	}
	minishell->var_search[j] = '\0';
	print_var_parsing(minishell);
	return (0);
}
