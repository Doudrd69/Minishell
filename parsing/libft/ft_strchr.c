/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:58:31 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/11 12:37:31 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr( const char *string, int searchedChar)
{
	int	count;

	count = 0;
	while (string[count] != '\0')
	{
		if (string[count] == (char)searchedChar)
			return ((char *)string + count);
		count++;
	}
	if (string[count] == (char)searchedChar)
		return ((char *)string + count);
	return (NULL);
}
