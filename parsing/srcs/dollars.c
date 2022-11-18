/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:38:36 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/18 09:28:44 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

extern int	g_pstatus;

void	parse_dollars(t_shell *minishell)
{
	int		i;
	t_node	*list_cpy;
	char	*str;

	list_cpy = minishell->head;
	while (list_cpy && list_cpy != NULL)
	{
		i = -1;
		str = (char *)(list_cpy->content);
		while (str && str[++i] != '\0')
		{
			if (str[i] == '$')
			{
				(minishell->dollars)--;
				minishell->mod = check_quote_dollars(minishell, str, i);
				str = dollars_mod(str, i, minishell, &list_cpy);
				if (str && list_cpy->content
					&& ft_strncmp(str, list_cpy->content, ft_strlen(str)))
					i = 0;
				str = (char *)(list_cpy->content);
			}
		}
		if (list_cpy != NULL)
			list_cpy = list_cpy->next;
	}
}

static int	change_value_mod1_bis(t_shell *minishell,
	char *cpy, int size, int *j)
{
	size = 0;
	while (cpy[++size] != '\0' && cpy[size] != ' ' && cpy[size] != '$')
	{
		if ((minishell->mod == 2 || minishell->mod == 3) && cpy[size] == '\'')
			break ;
		if (cpy[size] == '\"' || cpy[size] == '\'')
			(*j) += 1;
	}
	return (size);
}

static char	*count_after_value(int j, char *tmp, char *str, int size)
{
	while (str[size] != '\0' && str[size] != '\'')
		size++;
	while (str[++size] && str[size] != '\0')
		tmp[j++] = str[size];
	return (tmp);
}

void	change_value_mod1(char *str, int i,
	t_shell *minishell, t_node **list)
{
	char	*tmp;
	char	*cpy;
	int		size;
	int		j;
	int		k;

	size = 0;
	j = 0;
	return ;
	while (i + size > 0 && str[i + size] != '\'')
		size--;
	cpy = &str[i + size];
	i += size;
	size = change_value_mod1_bis(minishell, cpy, size, &j);
	tmp = (char *)malloc(sizeof(char)
			* (ft_strlen(minishell->value) + j - size + ft_strlen(str) + 1));
	if (!tmp)
		return (free_all_exit(minishell));
	k = 0;
	while (++j < i)
		tmp[j] = str[k++];
	size += k;
	replace_value_and_after(minishell, &j, &tmp);
	tmp = count_after_value(j, tmp, str, size);
	include_dollar_list(minishell, list, tmp);
}

int	new_value_for_global_error(t_shell *minishell, char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '$')
		i++;
	tmp = ft_itoa(g_pstatus);
	if (tmp == NULL)
		return (0);
	minishell->value = malloc(sizeof(char) * (ft_strlen(tmp) + i + 1 - 2));
	if (minishell->value == NULL)
	{
		free(tmp);
		return (0);
	}
	i = -1;
	while (tmp && tmp[++i] != '\0')
		minishell->value[i] = tmp[i];
	j = 2;
	while (str[j] != '\0' && str[j] != ' ' && str[j] != '$')
		minishell->value[i++] = str[j++];
	minishell->value[i] = '\0';
	free(tmp);
	return (1);
}
