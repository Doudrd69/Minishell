/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:10:48 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/24 11:54:25 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

unsigned int	ft_strlen(char *str);

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_check(char *base)
{
	int	i;
	int	j;
	int	blen;

	i = 0;
	j = 0;
	blen = ft_strlen(base);
	if (blen < 2)
		return (0);
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[j] == base[i] || base[j] == '+' || base[j] == '-')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr_base(int nbr, char *base)
{
	unsigned int	blen;
	long			bn;

	if (ft_check(base) == 1)
	{
		blen = ft_strlen(base);
		bn = nbr;
		if (nbr < 0)
		{
			ft_putchar('-');
			bn = -bn;
		}
		if (bn >= blen)
			ft_putnbr_base(bn / blen, base);
		ft_putchar(base[bn % blen]);
	}
}
