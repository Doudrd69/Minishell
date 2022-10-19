/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 12:24:08 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/24 11:24:59 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *base)
{
	int	i;

	i = 0;
	while (base[i])
		i++;
	return (i);
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
		if (base[i] == '+' || base[i] == '-' || base[i] == ' '
			|| base[i] == '\t' || base[i] == '\v' || base[i] == '\n'
			|| base[i] == '\r' || base[i] == '\f')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	ft_empt(char	*str, int	*i, int	*minus)
{
	while (str[*i] == '\t' || str[*i] == '\v' || str[*i] == '\n'
		|| str[*i] == '\r' || str[*i] == ' ' || str[*i] == '\f')
		*i = *i + 1;
	while (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			*minus = *minus * -1;
		*i = *i + 1;
	}
}

int	ft_gtp(char c, char *base)
{
	int	place;

	place = 0;
	while (base[place] != 0)
	{
		if (base[place] == c)
			return (place);
		place++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	bn;
	int	minus;

	i = 0;
	minus = 1;
	bn = 0;
	ft_empt(str, &i, &minus);
	while (ft_gtp(str[i], base) != -1 && str[i])
	{
		bn = bn * ft_strlen(base) + ft_gtp(str[i], base);
		i++;
	}
	return (bn * minus);
}
