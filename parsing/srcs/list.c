/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:39:22 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/12 19:39:22 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	empty_list(t_shell *minishell)
{
	if (minishell->list_size == 0 && minishell->head == NULL
		&& minishell->tail == NULL)
		return (1);
	return (0);
}
