/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:48:00 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/13 15:57:34 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	ft_putnbr_negative(int n, int fd)
{
	if (n < 0)
	{
		n = n * -1;
		write (fd, "-", 1);
	}
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	a;

	if (n == -2147483648)
	{
		write (fd, "-", 1);
		write (fd, "2", 1);
		n = 147483648;
	}
	n = ft_putnbr_negative(n, fd);
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	a = n % 10 + '0';
	write (fd, &a, 1);
}
