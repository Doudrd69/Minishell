/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:32:11 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/19 13:26:59 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_var(char *str, char *var_name)
{
	size_t	size;

	size = 0;
	while (str[size] != '=')
		size++;
	if (size == ft_strlen(var_name))
		return (1);
	return (0);
}

char	*mini_getenv(char *envp[], t_mini_data *mini_data, char *var_name)
{
	int		i;
	char	*str;

	i = 0;
	while (envp[i])
	{
		if (i == mini_data->envp_size)
		{
			ft_printf("\nCannot find %s\n", var_name);
			return (NULL);
		}
		if (ft_strnstr(envp[i], var_name, ft_strlen(var_name)))
			str = check_and_return_var(mini_data, envp, var_name, i);
		if (str != NULL)
			return (str);
		i++;
	}
	printf("Cannot find %s\n", var_name);
	return (NULL);
}

int	check_remains(char *str)
{
	int	i;

	i = 0;
	if (str[i + 1] == '\0')
	{
		write(1, "$", 1);
		return (0);
	}
	while (str[i + 1] != ' ')
		i++;
	i++;
	while (str[i] && (str[i] != '$'))
	{
		write(1, &str[i], 1);
		i++;
	}
	return (1);
}

char	*get_var_name(char *var)
{
	int		i;
	char	*str;

	i = 0;
	while (var[i])
	{
		if (var[i] == '=')
			break ;
		i++;
	}
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, var, i, 1);
	return (str);
}
