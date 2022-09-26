/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:13:24 by ebrodeur          #+#    #+#             */
/*   Updated: 2021/12/01 12:13:49 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_sort_params.h"
#include "../includes/ft_printf.h"

int	putnbr(int nb, int i)
{
	long int	a;

	a = nb;
	if (nb < 0)
	{
		a = -a;
		ft_putchar('-');
		i++;
	}
	if (a >= 10)
		i = putnbr(a / 10, i);
	ft_putchar(a % 10 + 48);
	return (i + 1);
}

int	putunbr(unsigned long int nb, int i)
{
	long int	a;

	a = nb;
	if (a >= 10)
		i = putnbr(a / 10, i);
	ft_putchar(a % 10 + 48);
	return (i + 1);
}

int	printmem(unsigned long long nb, char *base, int i)
{
	if (nb >= 16)
		i = printmem(nb / 16, base, i);
	print(nb % 16, base);
	return (i + 1);
}

int	putmem(unsigned long long *nb, char *base, int i)
{
	ft_putstr("0x");
	return (printmem(nb[0], base, i) + 2);
}

int	putnbr_hexa(unsigned int nb, int i, char *base)
{
	unsigned int	a;

	a = nb;
	if (a >= 16)
		i = putnbr_hexa(a / 16, i, base);
	print(a % 16, base);
	return (i + 1);
}
