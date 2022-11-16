/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:45:09 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/16 14:42:10 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	parse_quote(char *str, t_shell *minishell)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			str = ft_copy_string_without_quote(minishell, str, '"');
			ft_dlstadd_back((&(minishell)),
				ft_dlstnew((void *)str));
		}
		i++;
	}
}

char	*ft_copy_string_without_quote(t_shell *minishell, char *str, char quote)
{
	int		i;
	int		j;
	char	*newstr;

	j = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
			j++;
		i++;
	}
	newstr = malloc(sizeof(char) * (i - j + 1));
	if (!newstr)
		free_all_exit(minishell);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != quote)
			newstr[j++] = str[i];
		i++;
	}
	newstr[j] = '\0';
	return (newstr);
}
