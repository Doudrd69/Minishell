/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:58:09 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/12 16:20:21 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnstr( const char *haystack, const char *needle, size_t len)
{
	size_t	count;
	size_t	list;
	size_t	lenght;

	count = 0;
	lenght = ft_strlen(needle);
	if (needle[count] == '\0')
		return ((char *)haystack);
	while (count < len && haystack[count])
	{
		list = 0;
		while (count < len && haystack[count] == needle[list] && needle[list])
		{
			if (list == lenght - 1)
			{
				return ((char *)(haystack + count - list));
			}
			list++;
			count++;
		}
		count = count - list + 1;
	}
	return (NULL);
}
