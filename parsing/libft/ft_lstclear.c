/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 19:21:38 by wmonacho          #+#    #+#             */
/*   Updated: 2021/11/14 11:14:07 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tempi;
	t_list	*temple;

	if (!*lst || !del)
		return ;
	tempi = *lst;
	temple = *lst;
	while (tempi)
	{
		temple = temple->next;
		ft_lstdelone(tempi, (*del));
		tempi = temple;
	}
	*lst = NULL;
}
