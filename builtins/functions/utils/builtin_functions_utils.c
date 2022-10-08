/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functions_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 09:32:11 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/09/29 14:32:25 by ebrodeur         ###   ########lyon.fr   */
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

char	*mini_getenv(char *envp[], t_mini_data *mini_data, char *var_name)//enlever le \n du printf
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = -1;
	k = 0;
	while (envp[i])
	{
		if (i == mini_data->envp_size)
		{
			printf("\nCannot find %s\n", var_name);
			return (NULL);
		}
		if (ft_strnstr(envp[i], var_name, ft_strlen(var_name)))
		{
			if (check_var(envp[i], var_name))
			{
				mini_data->home_path = malloc(sizeof(char) * ft_strlen(envp[i]) + 1);
				if (!mini_data->home_path)
					return (NULL);
				while (envp[i][++j])
				{
					mini_data->home_path[k] = envp[i][j];
					k++;
				}
				mini_data->home_path[k] = '\0';
				return (mini_data->home_path);
			}
		}
		i++;
	}
	printf("Cannot find %s\n", var_name);
	return (NULL);
}

void	opendir_test(char *str, DIR *dir, struct dirent *pdir)//fonction pour ouvrir un dossier et lister ses fichiers
{
	dir = opendir(str);
	if (dir == NULL)
	{
		printf("Cannot open directory : %s\n", str);
		return ;
	}
	printf("DIRECTORY : %s\n", str);
	while ((pdir = readdir(dir)) != NULL)
		printf("FILE : %s\n", pdir->d_name);
	closedir(dir);
	return ;
}

int	check_remains(char *str)//supprimer un espace
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
