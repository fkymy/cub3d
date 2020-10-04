/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:32:55 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 18:25:37 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocation.h"
#include "game.h"

t_list		*g_allocations;

void		add_allocation(void *ptr)
{
	t_list *new;

	if (g_allocations == NULL)
	{
		if (!(g_allocations = ft_lstnew(ptr)))
			exit_with_message("Failed to allocate g_allocations. \n");
	}
	else
	{
		if (!(new = ft_lstnew(ptr)))
			exit_free("Failed to allocate g_allocations. \n");
		ft_lstadd_front(&g_allocations, new);
	}
}

void		*ft_malloc(size_t size)
{
	void *res;

	res = malloc(size);
	if (res)
		add_allocation(res);
	return (res);
}
