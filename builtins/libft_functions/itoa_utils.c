/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 10:51:59 by ebrodeur          #+#    #+#             */
/*   Updated: 2022/10/19 10:54:01 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*recursive_conversion(long int nbr, char *tab, int length)
{
	if (nbr >= 10)
		recursive_conversion(nbr / 10, tab, length - 1);
	tab[length - 1] = (nbr % 10 + 48);
	return (tab);
}

int	digit_count(long int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}
