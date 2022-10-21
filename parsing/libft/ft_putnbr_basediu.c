/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_basediu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: will <will@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:11:08 by wmonacho          #+#    #+#             */
/*   Updated: 2022/01/14 12:25:48 by will             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_taille(long nbr, int blen, int *i)
{
	int		minus;
	char	*ptr;

	minus = 0;
	if (nbr < 0)
	{
		minus = 1;
		nbr = -nbr;
	}
	*i = 0;
	while (nbr >= blen)
	{
		nbr = nbr / blen;
		(*i)++;
	}
	(*i)++;
	*i = *i + minus;
	ptr = malloc(sizeof(char) * (*i + 1));
	if (!ptr)
		return (NULL);
	if (minus == 1)
		ptr[0] = '-';
	return (ptr);
}

char	*ft_putnbr_basediu(long nbr, char *base_to)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = ft_taille(nbr, 10, &i);
	if (!ptr)
	{
		free(ptr);
		return (NULL);
	}
	j = i;
	if (nbr < 0)
		nbr = -nbr;
	ptr[j--] = '\0';
	while (nbr >= 10)
	{
		ptr[j--] = base_to[nbr % 10];
		nbr = nbr / 10;
	}
	ptr[j] = base_to[nbr % 10];
	return (ptr);
}
