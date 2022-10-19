/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:58:14 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/12 15:31:20 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		bille;
	int		count;

	count = ft_strlen(str);
	bille = 0;
	while (count > 0)
	{
		if (str[count] == (char)c)
		{
			return ((char *)(str + count));
		}
		bille++;
		count--;
	}
	if (str[count] == (char)c)
		return ((char *)(str + count));
	return (NULL);
}
