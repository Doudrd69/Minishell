/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_value_dollars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:43:20 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 20:06:10 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	new_value1(t_shell *minishell, char *str)
{
	int		size;

	size = 0;
	while (str[size] != '\0' && str[size] != ' ')
		size++;
	minishell->value = (char *)malloc(sizeof(char) * (size + 1));
	if (minishell->value == NULL)
		return (free_exit(minishell));
	size = -1;
	while (str[++size] != '\0' && str[size] != ' ')
		minishell->value[size] = str[size];
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
		return (free_exit(minishell));
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
			return (free_exit(minishell));
		while (str[cpy] != '\0' && str[cpy] != ' ')
			minishell->value[i++] = str[cpy++];
		minishell->value[i] = '\0';
	}
	return (1);
}

void	write_newvalue(t_shell *minishell, char *str, int mod, int i)
{
	if (mod == 0)
		new_value1(minishell, str);
	if (mod == 1 || mod == 7)
		new_value2(minishell, str);
	if (mod == 2 || mod == 5)
		new_value3(minishell, str, mod);
	if (mod == 3)
		new_value4(minishell, str);
	if (mod == 4)
		new_value5(minishell, str, i);
	if (mod == 6)
		new_value_mod2_and3(minishell, str, i);
}
