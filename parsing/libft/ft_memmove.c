/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:51:01 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/13 11:25:26 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t size)
{
	size_t	count;

	count = 0;
	if (!src)
		return (dest);
	if (dest <= src)
	{
		while (count < size)
		{
			((char *)dest)[count] = ((char *)src)[count];
				count++;
		}
	}
	if (dest > src)
	{
		while (count < size)
		{
			((char *)dest)[size - count -1] = ((char *)src)[size - count - 1];
				count++;
		}
	}
	return (dest);
}
