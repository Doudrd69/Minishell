/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:36:45 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/12 16:19:26 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memset( void *pointer, int value, size_t count)
{
	size_t	train;
	char	*point;

	train = 0;
	point = (char *)pointer;
	while (train < count)
	{
		point[train] = value;
		train++;
	}
	pointer = (void *)point;
	return (pointer);
}
