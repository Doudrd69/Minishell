/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_path_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 09:24:36 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/05/09 09:08:49 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cmd_include/pipex_bonus.h"

int	string_size(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**free_tab(char **tab, int i)
{
	printf("==== SIZE TO FREE : %d\n", i);
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (0);
}

int	ft_nb_w(const char *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			return (nb);
		while (s[i] && s[i] != c)
			i++;
		nb++;
	}
	return (nb);
}

char	*ft_custom_strcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	char	**tab;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_nb_w(s, c) + 1));
	if (!(tab))
		return (0);
	i = 0;
	j = 0;
	while (i < ft_nb_w(s, c))
	{
		while (s[j] == c)
			j++;
		tab[i] = malloc(sizeof(char) * string_size(&s[j], c) + 1);
		if (!(tab[i]))
			return (free_tab(tab, i));
		ft_custom_strcpy(tab[i], (char *)&s[j], string_size(&s[j], c));
		j += string_size(&s[j], c);
		i++;
	}
	tab[i] = 0;
	return (tab);
}
