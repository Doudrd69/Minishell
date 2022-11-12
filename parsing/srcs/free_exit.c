/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmonacho <wmonacho@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 20:38:23 by wmonacho          #+#    #+#             */
/*   Updated: 2022/11/12 20:52:01 by wmonacho         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

int	free_exit(t_shell *minishell)
{
	minishell += 0;
	exit(0);
	return (0);
}

/*
FREE ALL puis voir si on exit?
*/