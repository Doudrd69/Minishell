/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:38:36 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/14 12:32:30 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	parse_dollars(t_shell *minishell)
{
	int		i;
	t_node	*list_cpy;
	char	*str;
	int		dollars;

	dollars = minishell->nbr_dollars;
	list_cpy = minishell->head;
	while (list_cpy && list_cpy != NULL)
	{
		i = 0;
		str = (char *)(list_cpy->content);
		while (str && str[i] != '\0')
		{
			if (str[i] == '$')
			{
				dollars--;
				minishell->mod = check_quote_dollars(str);
				printf("%d\n", minishell->mod);
				dollars_mod(str, i, minishell, &list_cpy);
				str = (char *)(list_cpy->content);
			}
			i++;
		}
		if (list_cpy != NULL)
			list_cpy = list_cpy->next;
	}
}

static int	change_value_mod1_bis(t_shell *minishell, char *cpy, int size, int *j)
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

static void	change_value_mod1(char *str, int i,
	t_shell *minishell, t_node **list)
{
	char	*tmp;
	char	*cpy;
	int		size;
	int		j;
	int		k;

	size = 0;
	j = 0;
	while (i + size > 0 && str[i + size] != '\'')
		size--;
	cpy = &str[i + size];
	i += size;
	size = change_value_mod1_bis(minishell, cpy, size, &j);
	tmp = (char *)malloc(sizeof(char)
			* (ft_strlen(minishell->value) + j - size + ft_strlen(str) + 1));
	j = -1;
	k = 0;
	while (++j < i)
		tmp[j] = str[k++];
	size += k;
	replace_value_and_after(minishell, &j, &tmp);
	while (str[size] != '\0' && str[size] != '\'')
		size++;
	while (str[++size] && str[size] != '\0')
		tmp[j++] = str[size];
	include_dollar_list(minishell, list, tmp);
}

char	*dollars_mod(char *str, int i, t_shell *minishell, t_node **list)
{
	int	check;

	if (minishell->mod == 0 || minishell->mod == 2
		|| minishell->mod == 4 || minishell->mod == 3)
	{
		if (check_heredoc_dollar_mod_2_3(str, i) == 0)
		{
			printf("heredoc23\n");
			return (str);
		}
		if (check_heredoc_dollar_mod(str, i) == 0)
		{
			printf("heredoc\n");
			return (str);
		}
		check_and_print_var_parsing(minishell, str + i);
		if (minishell->value)
		{
			change_var_to_value(str, i, minishell, list);
		}
		else
		{
			check = check_dollars_mod(str + i);
			if (check == 2)
				check = check_dollar_export(str, i);
			if ((minishell->mod == 2 || minishell->mod == 3)
				&& str[i + 1] == ' ')
			{
				check = 6;
				write_newvalue(minishell, str, check, i);
				change_value_mod2_and_3(str, i, minishell, list);
			}
			else
			{
				write_newvalue(minishell, str + i, check, i);
				change_var_to_value(str, i, minishell, list);
			}
		}
	}
	else
	{
		if (check_heredoc_dollar_mod_1(str, i) == 0)
		{
			printf("heredoc1\n");
			return (str);
		}
		if (check_heredoc_dollar_mod(str, i) == 0)
		{
			printf("heredoc\n");
			return (str);
		}
		check = check_dollars_mod(str + i);
		if (minishell->mod == 1)
		{
			check = 4;
			write_newvalue(minishell, str, check, i);
			change_value_mod1(str, i, minishell, list);
		}
		else
		{
			write_newvalue(minishell, str + i, check, i);
			change_var_to_value(str, i, minishell, list);
		}
	}
	return (str);
}
