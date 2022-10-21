/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:58:53 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/12 16:18:33 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memchr( const void *memoryBlock, int searchedChar, size_t size)
{
	size_t				count;
	unsigned char		*memblock;

	memblock = (unsigned char *)memoryBlock;
	count = 0;
	while (count < size)
	{
		if (memblock[count] == (unsigned char)searchedChar)
		{
			return (memblock + count);
		}
		count++;
	}
	return (NULL);
}
