/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parse_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 23:40:34 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/09 16:59:14 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	skip_spaces(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
}

void	skip_digits(char **line)
{
	while (ft_isdigit(**line))
		(*line)++;
}

int		is_empty_line(char *line)
{
	int is_empty;

	is_empty = 1;
	while (*line)
	{
		if (!ft_isspace(*line))
			is_empty = 0;
		line++;
	}
	return (is_empty);
}

char	*ft_strjoin_delim(char *s1, char delim, char *s2)
{
	char	*res;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(s1) + 1 + ft_strlen(s2);
	if (!(res = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		res[i++] = s1[j++];
	res[i++] = delim;
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_strjoin_delim_free(char *s1, char delim, char *s2)
{
	char *res;

	res = ft_strjoin_delim(s1, delim, s2);
	free(s1);
	return (res);
}
