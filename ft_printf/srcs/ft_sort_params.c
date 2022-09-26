/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:33:13 by ebrodeur          #+#    #+#             */
/*   Updated: 2021/12/01 12:10:47 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_sort_params.h"
#include "../includes/ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

void	print(int i, char *tab)
{
	char	c;

	c = tab[i];
	ft_putchar(c);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

int	ft_sort_params(char c, va_list args)
{
	int					i;
	unsigned long long	p;

	if (c == 'c')
		i = ft_putchar(va_arg(args, int));
	if (c == '%')
		i = ft_putchar('%');
	if (c == 's')
		i = ft_putstr(va_arg(args, char *));
	if (c == 'p')
	{
		p = va_arg(args, unsigned long long);
		i = putmem(&p, "0123456789abcdef", 0);
	}
	if (c == 'd' || c == 'i')
		i = putnbr(va_arg(args, int), 0);
	if (c == 'u')
		i = putunbr(va_arg(args, unsigned int), 0);
	if (c == 'x')
		i = putnbr_hexa(va_arg(args, unsigned int), 0, "0123456789abcdef");
	if (c == 'X')
		i = putnbr_hexa(va_arg(args, unsigned int), 0, "0123456789ABCDEF");
	return (i);
}
