/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_adr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:34:49 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/24 15:56:47 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_taille(long nbr, int blen, int *i)
{
	char	*ptr;

	*i = 0;
	while (nbr >= blen)
	{
		nbr = nbr / blen;
		*i++;
	}
	*i++;
	ptr = (char *)malloc(sizeof(char) * (*i + 3));
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}

int	ft_put_adr(unsigned long long nbr, char *base_to)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = ft_taille(nbr, 16, &i);
	j = i;
	if (!ptr)
		return (-1);
	ptr[j] = '\0';
	j--;
	while (nbr >= 16)
	{
		ptr[j] = base_to[nbr % 16];
		nbr = nbr / 16;
		j--;
	}
	ptr[j] = base_to[nbr % 16];
	ptr[0] = '0';
	ptr[1] = 'x';
	ft_putstr_fd(ptr, 1);
	return (i);
}
