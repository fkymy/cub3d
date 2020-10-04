/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 13:16:07 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 15:35:39 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# if defined(__APPLE__)
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_S 1
#  define KEY_W 13
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_ESC 53
# else
#  define KEY_A 0x0061
#  define KEY_D 0x0064
#  define KEY_S 0x0073
#  define KEY_W 0x0077
#  define KEY_LEFT 0xff51
#  define KEY_RIGHT 0xff53
#  define KEY_UP 0xff52
#  define KEY_DOWN 0xff54
#  define KEY_ESC 0xff1b
# endif

#endif
