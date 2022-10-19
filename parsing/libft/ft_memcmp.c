/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:58:39 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/13 11:16:08 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_memcmp( const void *ptr, const void *str, size_t size)
{
	size_t			count;
	unsigned char	*ptrr;
	unsigned char	*strr;

	count = 0;
	ptrr = (unsigned char *)ptr;
	strr = (unsigned char *)str;
	while (count < size)
	{
		if (ptrr[count] > strr[count])
			return (ptrr[count] - strr[count]);
		if (ptrr[count] < strr[count])
			return (ptrr[count] - strr[count]);
		count++;
	}
	return (0);
}
