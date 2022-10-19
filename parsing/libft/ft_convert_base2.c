/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:55:18 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/24 13:55:22 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		ft_atoi_base(char *str, char *base);

int		ft_strlen(char	*base);

int		ft_check(char *base);

char	*ft_putnbr_base(long nbr, char *base_to);

char	*ft_taille(long nbr, int blen)
{
	int		i;
	int		minus;
	char	*ptr;

	minus = 0;
	if (nbr < 0)
	{
		minus = 1;
		nbr = -nbr;
	}
	i = 0;
	while (nbr >= blen)
	{
		nbr = nbr / blen;
		i++;
	}
	i++;
	i = i + minus;
	ptr = malloc(sizeof(char) * (i + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[0] = i;
	return (ptr);
}

char	*ft_convert_base(char *str, char *base_from, char *base_to)
{
	long		nbr;
	char		*ptr;
	int			blen;

	if (ft_check(base_from) == 1 && ft_check(base_to) == 1)
	{
		nbr = ft_atoi_base(str, base_from);
		blen = ft_strlen(base_to);
		ptr = ft_putnbr_base(nbr, base_to);
		return (ptr);
	}
	return (NULL);
}

char	*ft_putnbr_base(long nbr, char *base_to)
{
	int		blen;
	char	*ptr;
	int		i;

	blen = ft_strlen(base_to);
	ptr = ft_taille(nbr, blen);
	if (ptr == NULL)
		return (NULL);
	i = ptr[0];
	if (nbr < 0)
	{
		ptr[0] = '-';
		nbr = -nbr;
	}
	ptr[i] = '\0';
	i--;
	while (nbr >= blen)
	{
		ptr[i] = base_to[nbr % blen];
		nbr = nbr / blen;
		i--;
	}
	ptr[i] = base_to[nbr % blen];
	return (ptr);
}
