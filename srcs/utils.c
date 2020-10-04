/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 15:44:30 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/07 23:48:07 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "game.h"

int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
			c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}