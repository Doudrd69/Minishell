/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:17:01 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/16 20:27:13 by wmonacho         ###   ########lyon.fr   */
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

void	change_var_to_value(char *str, int i, t_shell *minishell, t_node **list)
{
	char	*tmp;
	char	*cpy;
	int		size;
	int		j;
	int		k;

	size = 0;
	j = 0;
	cpy = &str[i];
	if (minishell->mod == 6)
		return;
	if (i > 0 && str[i - 1] == '\"' && minishell->mod == 2)
		j++;
	while (cpy[++size] != '\0' && cpy[size] != ' ' && cpy[size] != '$')
	{
		if (minishell->mod == 2 && cpy[size] == '\"')
			break ;
		if (cpy[size] == '\"' || cpy[size] == '\'')
			j++;
	}
	tmp = (char *)malloc(sizeof(char)
			* (ft_strlen(minishell->value) + j - size + ft_strlen(str) + 1));
	dprintf(2, "j=%d|val=%s|str=%s|size=%d|cpy=%s|cpy+size=%s\n", j, minishell->value, str, size, cpy, cpy + size);
	dprintf(2, "len_malloc=%lu=\n", (ft_strlen(minishell->value) + j - size + ft_strlen(str) + 1));
	return_malloc_change_var(minishell, tmp, cpy);
	j = -1;
	k = 0;
	while (++j < i)
		tmp[j] = str[k++];
	size += k;
	if (i > 0 && str[i - 1] == '\"' && str[size - 1] == '\"'  && minishell->mod == 2)
		size --;
	replace_value_and_after(minishell, &j, &tmp);
	while (str[size] && str[size] != '\0')
		tmp[j++] = str[size++];
	printf("j=%d=\n", j);
	tmp = replace_quote_dollars(minishell, tmp, j);
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

void	value_quote_mod_1(t_shell *minishell, char *str, int i)
{
	int	check;

	check = 4;
	write_newvalue(minishell, str, check, i);
}
