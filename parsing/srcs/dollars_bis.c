/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:17:01 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/17 19:46:59 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	replace_value_and_after(t_shell *minishell, int *j, char **tmp)
{
	int	k;

	k = 0;
	while (minishell->value && minishell->value[k] != '\0')
		(*tmp)[(*j)++] = minishell->value[k++];
}

static void	count_malloc_new_tmp(t_shell *minishell, int *i, int *j, int *size)
{
	char	*cpy;

	cpy = &(minishell->strd[*i]);
	if (*i > 0 && minishell->strd[*i - 1] == '\"' && minishell->mod == 2)
		(*j)++;
	while (cpy[++(*size)] != '\0' && cpy[*size] != '$'
		&& cpy[*size] != '/' && cpy[*size] != '=')
	{
		if (cpy[*size] == ' ' && minishell->mod != 4)
			break ;
		if ((minishell->mod == 2 && cpy[*size] == '\"')
			|| (minishell->mod == 4 && cpy[*size] == '\"'))
			break ;
		if (cpy[*size] == '\"' || cpy[*size] == '\'')
			(*j)++;
	}
	if (minishell->mod == 4)
		(*j)++;
}

static void	fill_before_value_tmp(t_shell *minishell,
	int *j, char **tmp, int *size)
{
	int	k;

	(*j) = -1;
	k = 0;
	while (++(*j) < (minishell->i))
		(*tmp)[*j] = minishell->strd[k++];
	(*size) += k;
	if (minishell->i > 0 && minishell->strd[(minishell->i) - 1] == '\"'
		&& minishell->strd[(*size) - 1] == '\"'
		&& minishell->mod == 2)
		(*size)--;
}

void	change_var_to_value(char *str, int i, t_shell *minishell, t_node **list)
{
	char	*tmp;
	char	*cpy;
	int		size;
	int		j;

	size = 0;
	j = 0;
	cpy = &str[i];
	minishell->strd = str;
	if (minishell->mod == 6)
<<<<<<< HEAD
		return ;
	count_malloc_new_tmp(minishell, &i, &j, &size);
=======
		return;
	if (i > 0 && str[i - 1] == '\"' && minishell->mod == 2)
		j++;
	while (cpy[++size] != '\0' && cpy[size] != '$' && cpy[size] != '/' && cpy[size] != '=')
	{
		printf("MDR\n");
		if (cpy[size] == ' ' && minishell->mod != 4)
			break ;
		if ((minishell->mod == 2 && cpy[size] == '\"') || (minishell->mod == 4 && cpy[size] == '\"'))
			break ;
		if (cpy[size] == '\"' || cpy[size] == '\'')
			j++;
	}
	if (minishell->mod == 4)
		j++;
>>>>>>> 02737633c8ad3c7c022162948177bef7be8005c4
	tmp = (char *)malloc(sizeof(char)
			* (ft_strlen(minishell->value) + j - size + ft_strlen(str) + 1));
	return_malloc_change_var(minishell, tmp, cpy);
	minishell->i = i;
	fill_before_value_tmp(minishell, &j, &tmp, &size);
	replace_value_and_after(minishell, &j, &tmp);
	tmp = replace_quote_dollars(minishell, tmp, &j);
	while (str[size] && str[size] != '\0')
		tmp[j++] = str[size++];
	tmp[j] = '\0';
	include_dollar_list(minishell, list, tmp);
}

int	check_heredoc_dollar_mod_2_3(char *str, int i)
{
	int	j;
	int	tpm;

	tpm = i;
	while (str[tpm] != '\0' && str[tpm] != '\"')
		tpm++;
	if (str[tpm] == '\0')
		return (1);
	j = tpm;
	if (i == 0)
		return (1);
	i--;
	while (i > 0 && str[i] == ' ')
		i--;
	while (i > 0 && str[i] == '\"')
		i--;
	while (i > 0 && str[i] == ' ')
		i--;
	if (i < 1)
		return (1);
	if (str[i] == '<' && str[i - 1] == '<')
		return (0);
	return (1);
}
