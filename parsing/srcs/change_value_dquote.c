/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_value_dquote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:53:31 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 13:20:42 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

static int	change_value_mod2_and_3_bis(t_shell *minishell,
	char *cpy, int size, int *j)
{
	size = 0;
	while (cpy[++size] != '\0' && cpy[size] != ' ' && cpy[size] != '$')
	{
		if ((minishell->mod == 2 || minishell->mod == 3) && cpy[size] == '\"')
			break ;
		if (cpy[size] == '\"' || cpy[size] == '\'')
			(*j) += 1;
	}
	return (size);
}

static char	*count_after_value(int j, char *tmp, char *str, int size)
{
	while (str[size] != '\0' && str[size] != '\"')
		size++;
	while (str[++size] && str[size] != '\0')
		tmp[j++] = str[size];
	return (tmp);
}

void	change_value_mod2_and_3(char *str, int i,
	t_shell *minishell, t_node **list)
{
	char	*tmp;
	char	*cpy;
	int		size;
	int		j;
	int		k;

	size = 0;
	j = 0;
	while (i + size > 0 && (str[i + size] != '\"' && str[i + size] != '\''))
		size--;
	cpy = &str[i + size];
	i += size;
	size = change_value_mod2_and_3_bis(minishell, cpy, size, &j);
	tmp = (char *)malloc(sizeof(char)
			* (ft_strlen(minishell->value) + j - size + ft_strlen(str) + 1));
	j = -1;
	k = 0;
	while (++j < i)
		tmp[j] = str[k++];
	size += k;
	replace_value_and_after(minishell, &j, &tmp);
	tmp = count_after_value(j, tmp, str, size);
	include_dollar_list(minishell, list, tmp);
}
