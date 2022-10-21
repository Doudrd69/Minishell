/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 12:23:55 by wmonacho          #+#    #+#             */
/*   Updated: 2022/10/18 13:24:07 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	**ft_free(int k, char **tab)
{
	while (k > 0)
	{
		free(tab[k]);
		k--;
	}
	free(tab);
	return (NULL);
}

static int	ft_nbr_words(char const	*str, char charset)
{
	int	nbrw;
	int	i;

	nbrw = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == charset && str[i])
		{
			i++;
		}
		if (str[i] != charset && str[i])
			nbrw++;
		while (str[i] != charset && str[i])
		{
			i++;
		}
	}
	return (nbrw);
}

static int	ft_malloc_ws(char const	*str, char charset, char **tab)
{
	int	i;
	int	wlen;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		wlen = 0;
		while (str[i] == charset && str[i])
			i++;
		while (str[i] != charset && str[i])
		{
			i++;
			wlen++;
		}
		tab[j] = (char *)malloc(sizeof(char) * (wlen + 1));
		if (tab[j] == NULL)
			return (j);
		if (str[i] == charset || str[i] == '\0')
			j++;
		while (str[i] == charset && str[i])
			i++;
	}
	return (0);
}

static char	**ft_get_filling(char const *str, char charset, char	**tab)
{
	int	i;
	int	x;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		while (str[i] == charset && str[i])
			i++;
		x = 0;
		while (str[i] != charset && str[i])
			tab[k][x++] = str[i++];
		tab[k][x] = '\0';
		if (str[i] == charset || str[i - x] != '\0')
			k++;
		while (str[i] == charset && str[i])
			i++;
	}
	return (tab);
}

char	**ft_split(char const *str, char c)
{
	char	**tab;
	int		nbrw;

	if (!str)
		return (NULL);
	nbrw = ft_nbr_words(str, c);
	tab = (char **)malloc(sizeof(char *) * (nbrw + 1));
	if (tab == NULL)
		return (NULL);
	tab[nbrw] = 0;
	if (nbrw == 0)
		return (tab);
	if (ft_malloc_ws(str, c, tab))
		return (ft_free(ft_malloc_ws(str, c, tab), tab));
	tab = ft_get_filling(str, c, tab);
	return (tab);
}
