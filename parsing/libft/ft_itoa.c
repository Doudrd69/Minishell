/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:24:00 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/13 10:39:02 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_len(long m)
{
	int	len;

	len = 0;
	while (m >= 10)
	{
		m = m / 10;
		len++;
	}
	len++;
	return (len);
}

static void	ft_get_filling(char *itoa, int len, int minus, long m)
{
	while (m >= 10)
	{
		itoa[len + minus] = (m % 10) + '0';
		m = m / 10;
		len--;
	}
	itoa[len + minus] = m % 10 + '0';
}

char	*ft_itoa( int n)
{
	int		len;
	int		minus;
	long	m;
	char	*itoa;

	minus = 0;
	len = 0;
	m = (long)n;
	if (m < 0)
	{
		m = m * -1;
		minus = 1;
	}
	len = ft_len(m);
	itoa = (char *)malloc(sizeof(char) * (len + 1 + minus));
	if (itoa == NULL)
		return (NULL);
	if (minus == 1)
		itoa[0] = '-';
	itoa[len + minus] = '\0';
	len--;
	ft_get_filling(itoa, len, minus, m);
	return (itoa);
}
