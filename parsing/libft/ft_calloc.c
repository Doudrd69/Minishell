/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:49:24 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/12 16:22:56 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc( size_t elementCount, size_t elementSize)
{
	size_t		count;
	void		*dest;

	count = 0;
	dest = malloc(elementCount * elementSize);
	if (dest == NULL)
		return (NULL);
	while (count < elementCount * elementSize)
	{
		((char *)dest)[count] = 0;
		count++;
	}
	return (dest);
}
