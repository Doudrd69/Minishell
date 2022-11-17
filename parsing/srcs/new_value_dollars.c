/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_value_dollars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:43:20 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/17 12:06:55 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	new_value1(t_shell *minishell, char *str)
{
	int		size;
	int		i;

	size = 1;
	while (str && str[size] != '\0' && str[size] != ' ' && str[size] != '$')
		size++;
	minishell->value = (char *)malloc(sizeof(char) * (size + 2));
	if (minishell->value == NULL)
		return (0);
	size = 0;
	i = 0;
	minishell->value[i++] = '$';
	while (str[++size] != '\0' && str[size] != ' ' && str[size] != '$')
		minishell->value[i++] = str[size];
	minishell->value[size] = '\0';
	return (1);
}

static int	new_value2(t_shell *minishell, char *str)
{
	int	size;
	int	i;

	size = 0;
	while (str[size] != '\0' && str[size] != ' ')
		size++;
	minishell->value = (char *)malloc(sizeof(char) * (size - 1));
	if (minishell->value == NULL)
		return (0);
	size = 1;
	i = -1;
	while (str[++size] != '\0' && str[size] != ' ')
	{
		minishell->value[++i] = str[size];
	}
	minishell->value[++i] = '\0';
	return (1);
}

static void	new_value3_bis(int *cpy, char *str, int *i, int *size)
{
	*cpy = *i;
	while (str[*i] != '\0' && str[(*i)++] != ' ')
		(*size) += 1;
	*i = 0;
}

static int	new_value3(t_shell *minishell, char *str, int mod)
{
	int	size;
	int	cpy;
	int	i;

	i = 0;
	size = 0;
	if (mod != 2)
	{
		new_value3_bis(&cpy, str, &i, &size);
		if (size == 0)
		{
			minishell->value = NULL;
			return (1);
		}
		minishell->value = malloc(sizeof(char) * (size + 1));
		if (minishell->value == NULL)
			return (0);
		while (str[cpy] != '\0' && str[cpy] != ' ')
			minishell->value[i++] = str[cpy++];
		minishell->value[i] = '\0';
	}
	return (1);
}

void	write_newvalue(t_shell *minishell, char *str, int mod, int i)
{
	if (mod == 0)
		if (new_value1(minishell, str) == 0)
			return (free_all_exit(minishell));
	if (mod == 1 || mod == 7)
		if (new_value2(minishell, str) == 0)
			return (free_all_exit(minishell));
	if (mod == 2 || mod == 5)
		if (new_value3(minishell, str, mod) == 0)
			return (free_all_exit(minishell));
	if (mod == 3)
		if (new_value4(minishell, str) == 0)
			return (free_all_exit(minishell));
	if (mod == 4)
		if (new_value5(minishell, str, i) == 0)
			return (free_all_exit(minishell));
	if (mod == 6)
		if (new_value_mod2_and3(minishell, str, i) == 0)
			return (free_all_exit(minishell));
}
