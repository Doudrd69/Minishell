/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_value_dollars_bis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:35:10 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/16 15:57:23 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	new_value_mod2_and3(t_shell *minishell, char *str, int i)
{
	int	size;
	int	j;

	size = 0;
	while (i + size > 0 && str[i + size] != '\"')
		size--;
	i += size;
	size = 1;
	while (str[++i] != '\0' && str[i] != '\"')
		size++;
	minishell->value = (char *)malloc(sizeof(char) * (size + 1));
	if (minishell->value == NULL)
		return (0);
	j = 0;
	minishell->value[j++] = '\"';
	i -= size;
	while (str[++i] != '\0' && str[i] != '\"')
		minishell->value[j++] = str[i];
	if (str[i] == '\"')
		minishell->value[j++] = str[i];
	minishell->value[j] = '\0';
	return (1);
}

int	new_value5(t_shell *minishell, char *str, int i)
{
	int	size;
	int	j;

	size = 0;
	while (i + size > 0 && str[i + size] != '\'')
		size--;
	i += size;
	size = 1;
	while (str[++i] != '\0' && str[i] != '\'')
		size++;
	minishell->value = (char *)malloc(sizeof(char) * (size + 2));
	if (minishell->value == NULL)
		return (0);
	j = 0;
	minishell->value[j++] = '\'';
	i -= size;
	while (str[++i] != '\0' && str[i] != '\'')
		minishell->value[j++] = str[i];
	if (str[i] == '\'')
		minishell->value[j++] = str[i];
	minishell->value[j] = '\0';
	return (1);
}

int	new_value4(t_shell *minishell, char *str)
{
	int	size;
	int	i;

	size = 0;
	while (str[size] != '\0' && str[size] != ' ')
		size++;
	minishell->value = (char *)malloc(sizeof(char) * (size));
	if (minishell->value == NULL)
		return (0);
	size = 0;
	i = 0;
	while (str[++size] != '\0' && str[size] != ' ')
		minishell->value[i++] = str[size];
	minishell->value[size] = '\0';
	return (1);
}
