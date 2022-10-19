/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebrodeur <ebrodeur@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:06:43 by wmonacho          #+#    #+#             */
/*   Updated: 2022/10/19 18:30:02 by ebrodeur         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	ft_dlstadd_back(t_shell **alst, t_node *new)
{
	t_shell	*temp;

	if (new)
	{
		if (!*alst)
		{
			(*alst)->head = new;
			(*alst)->tail = new;
		}
		else
		{
			temp = (*alst);
			temp->tail->next = new;
			new->prev = temp->tail;
			temp->tail = new;
		}
		(*alst)->list_size += 1;
		return (1);
	}
	return (0);
}
