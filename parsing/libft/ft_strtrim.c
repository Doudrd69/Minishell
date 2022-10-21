/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:40:02 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/18 10:28:40 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_cmp(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static void	ft_trim(char const *s1, char const *set, int *i, int *j)
{
	int	k;
	int	l;

	k = 0;
	l = ft_strlen(s1) - 1;
	*i = 0;
	*j = 0;
	while (ft_cmp(s1[k], set) && s1[k])
	{
		*i = *i + 1;
		k++;
	}
	while (ft_cmp(s1[l], set) && l > 0 && *i != l + 1)
	{
		*j = *j + 1;
		l--;
	}
}

static void	ft_get_filling(char	*trimmer, int countstart, int countend,
char const *s1)
{
	int	i;
	int	j;
	int	end;

	i = 0;
	j = countstart;
	end = ft_strlen(s1);
	while (i < end - countend - countstart)
	{
		trimmer[i] = s1[j];
		i++;
		j++;
	}
	trimmer[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmer;
	int		j;
	int		i;
	int		len1;

	if (!s1 || !set)
		return (NULL);
	len1 = ft_strlen(s1);
	ft_trim(s1, set, &i, &j);
	trimmer = (char *)malloc(sizeof(char) * (len1 - (i + j) + 1));
	if (!trimmer)
		return (NULL);
	ft_get_filling(trimmer, i, j, s1);
	return (trimmer);
}
