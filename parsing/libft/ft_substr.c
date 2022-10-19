/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:51:05 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/18 10:26:39 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

char	*ft_substr( char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	count;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
	{
		dest = malloc(1);
		dest[0] = '\0';
		return (dest);
	}
	count = ft_strlen(s) - start;
	if (len < count)
		count = len;
	dest = (char *)malloc(sizeof(char) * (count + 1));
	count = 0;
	if (dest == NULL)
		return (NULL);
	while (count < len && s[start])
		dest[count++] = s[start++];
	dest[count] = '\0';
	return (dest);
}
