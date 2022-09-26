/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 09:47:26 by ebrodeur          #+#    #+#             */
/*   Updated: 2021/12/01 12:05:09 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/ft_sort_params.h"

int	ft_printf(const char *flags, ...)
{
	va_list	args;
	int		i;
	int		result;

	va_start(args, flags);
	i = 0;
	result = 0;
	while (flags[i])
	{
		if (flags[i] == '%')
		{
			i++;
			if (flags[i] == '\0')
				return (0);
			result += ft_sort_params(flags[i], args);
		}
		else
		{
			ft_putchar(flags[i]);
			result++;
		}
		i++;
	}
	va_end(args);
	return (result);
}
