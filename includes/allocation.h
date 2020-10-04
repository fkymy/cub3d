/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 17:32:18 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 17:43:39 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOCATION_H
# define ALLOCATION_H

# include "../libft/libft.h"

extern t_list	*g_allocations;

void			add_allocation(void *ptr);
void			*ft_malloc(size_t size);

#endif
