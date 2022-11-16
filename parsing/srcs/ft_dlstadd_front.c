/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 17:10:08 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/15 13:47:00 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	ft_dlstadd_front(t_shell **alst, t_node *new)
{
	t_node	*temp;

	if (new)
	{
		temp = (*alst)->head;
		if (temp)
		{
			temp->prev = new;
			new->next = temp;
		}
		(*alst)->head = new;
		(*alst)->list_size += 1;
		return (1);
	}
	return (0);
}
