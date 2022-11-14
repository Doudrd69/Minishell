/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_infile_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:13:58 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/11/14 17:16:36 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	main_loop_search_infile(char *str, int i, int file)
{
	while (str[i] != '\0' && str[i] != ' ' && (str[i] != '<' && str[i] != '>'))
	{
		if (str[i] == '\"' && str[i + 1] != '\0')
		{
			while (str[++i] != '\"' && str[i] != '\0')
				file++;
			if (str[i] == '\"')
				file++;
		}
		if (str[i] == '\'' && str[i + 1] != '\0')
		{
			while (str[++i] != '\'')
				file++;
		}
		file++;
		i++;
	}
	return (file);
}

int	dl_fl_search_infile(char *str, int i)
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
