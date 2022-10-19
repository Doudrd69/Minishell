/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 08:54:14 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/12 16:12:01 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, unsigned int size)
{
	unsigned int	i2;
	unsigned int	src_len;
	unsigned int	dest_len;
	unsigned int	j;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	i2 = 0;
	if (size == 0 || size < dest_len)
		return (src_len + size);
	j = dest_len;
	while (src[i2] && j < size - 1)
	{
		dest[j] = src[i2];
		i2++;
		j++;
	}
	dest[j] = 0;
	return (dest_len + src_len);
}
