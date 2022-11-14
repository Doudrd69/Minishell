/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_outfile_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:00:37 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 17:11:11 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	main_loop_dl_fl(char *str, int i)
{
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\"' && str[i + 1] != '\0')
		{
			i++;
			while (str[i] != '\"' && str[i] != '\0')
				i++;
		}
		if (str[i] == '\'' && str[i + 1] != '\0')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}

int	main_loop_search_outfile(t_shell *s, char *str, int i)
{
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\"' && str[i + 1] != '\0')
		{
			while (str[++i] != '\"' && str[i] != '\0')
				s->file_search++;
			if (str[i] == '\"')
				s->file_search++;
		}
		if (str[i] == '\'' && str[i + 1] != '\0')
		{
			while (str[++i] != '\'')
				s->file_search++;
		}
		s->file_search++;
		i++;
	}
	return (i);
}
