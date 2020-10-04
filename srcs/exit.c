/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 19:02:14 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 19:24:21 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation.h"
#include "game.h"

void	exit_with_message(char *s)
{
	int len;

	len = ft_strlen(s);
	write(1, s, len);
	exit(1);
}

void	exit_free(char *s)
{
	ft_lstclear(&g_allocations, free);
	exit_with_message(s);
}
