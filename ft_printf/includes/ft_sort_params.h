/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:35:14 by ebrodeur          #+#    #+#             */
/*   Updated: 2021/12/01 12:13:41 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SORT_PARAMS_H
# define FT_SORT_PARAMS_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_putchar(char c);
int		ft_putstr(char *str);
int		putnbr(int nb, int i);
void	print(int i, char *tab);
int		putunbr(unsigned long int nb, int i);
int		putnbr_hexa(unsigned int nb, int i, char *base);
int		putmem(unsigned long long *nb, char *base, int i);
int		putnbr_adresshexa(unsigned long long nb, int i, char *base);

#endif
