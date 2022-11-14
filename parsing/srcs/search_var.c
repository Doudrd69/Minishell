/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:40:34 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 16:57:39 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	find_position_of_dollars(char *position, int i, int *size)
{
	while (position[*size] != '\0' && position[*size] != ' ')
	{
		if (position[*size] == '$' && *size != 0)
			break ;
		if (position[*size] == '\"' || position[*size] == '\'')
			i++;
		(*size)++;
	}
	*size -= i;
}

static void	ft_find_dollars(t_shell *minishell, char *var, int *size, int *i)
{
	char	*position;

	position = &minishell->var_search[0];
	while (position[*size] != '\0' && position[*size] != ' '
		&& position[*size] != '\"')
	{
		if (position[*size] == '$' && *size != 0)
			break ;
		(*size)++;
	}
	while (var[*i] != ' ' && var[*i] != '\0')
		(*i)++;
}

char	*check_and_return_var_parsing(char *home_path,
	char **envp, char *var, int i)
{
	int	j;
	int	k;

	j = -1;
	k = 0;
	if (check_var_parsing(envp[i], var))
	{
		home_path = malloc(sizeof(char) * ft_strlen(envp[i]) + 1);
		if (!home_path)
			return (NULL);
		while (envp[i][++j])
		{
			home_path[k] = envp[i][j];
			k++;
		}
		home_path[k] = '\0';
		return (home_path);
	}
	return (NULL);
}

char	*mini_getenv_parsing(char *envp[], int env_size,
	char *var_name, t_shell *minishell)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (envp[i])
	{
		if (i == env_size)
		{
			printf("\nCannot find %s\n", var_name);
			return (NULL);
		}
		if (ft_strnstr(envp[i], var_name, ft_strlen(var_name)))
		{
			str = check_and_return_var_parsing(minishell->home_path,
					envp, var_name, i);
		}
		if (str != NULL)
			return (str);
		i++;
	}
	printf("Cannot find %s\n", var_name);
	return (NULL);
}

void	print_var_parsing(t_shell *minishell)
{
	int		size;
	int		i;
	int		j;
	char	*var;

	size = 0;
	i = 0;
	if (var_exists_parsing(minishell))
	{
		var = mini_getenv_parsing(minishell->env_search,
				minishell->env_size, minishell->var_search, minishell);
		j = 0;
		while (var[j] && var[j] != '=')
			j++;
		ft_find_dollars(minishell, var, &size, &i);
		minishell->value = malloc(sizeof(char) * (i + 1));
		if (!(minishell->value))
			return ;
		j++;
		copy_value_parsing(minishell, j, i, var);
		free(var);
	}
	else
		minishell->value = NULL;
	return ;
}
