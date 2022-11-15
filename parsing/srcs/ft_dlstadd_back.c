/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 18:06:43 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/15 13:47:39 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	ft_dlstadd_back(t_shell **alst, t_node *new)
{
	t_node	*temp;

	temp = (*alst)->head;
	if (new)
	{
		if (!temp)
			(*alst)->head = new;
		else
		{
			while (temp->next)
				temp = temp->next;
			temp->next = new;
			new->prev = temp;
		}
		(*alst)->list_size += 1;
		return (1);
	}
	return (0);
}
