/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:10:08 by wmonacho          #+#    #+#             */
/*   Updated: 2022/10/21 12:59:44 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	ft_dlstadd_front(t_shell **alst, t_node *new)
{
	t_shell	*temp;

	if (new)
	{
		if (!*alst)
		{
			(*alst)->tail = new;
			(*alst)->head = new;
		}
		else
		{
			temp = (*alst);
			temp->head->prev = new;
			new->next = temp->head;
			temp->head = new;
		}
		(*alst)->list_size += 1;
		return (1);
	}
	return (0);
}
