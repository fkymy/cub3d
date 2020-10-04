/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yufukuya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 18:11:29 by yufukuya          #+#    #+#             */
/*   Updated: 2020/08/02 15:11:35 by yufukuya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	handle_success(int ret, char **buf)
{
	free(*buf);
	*buf = NULL;
	return (ret);
}

static int	handle_error(char **str, char **buf)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	if (*buf)
	{
		free(*buf);
		*buf = NULL;
	}
	return (ERROR);
}

static int	newline_or_eof(char **line, char **str, char *nl, char **buf)
{
	char *tmp;

	if (nl)
	{
		*line = gnl_strndup(*str, nl - *str);
		if (*line == NULL)
			return (handle_error(str, buf));
		tmp = gnl_strndup(nl + 1, gnl_strlen(nl + 1));
		free(*str);
		*str = tmp;
		if (*str == NULL)
		{
			free(*line);
			*line = NULL;
			return (handle_error(str, buf));
		}
		return (handle_success(NEXT, buf));
	}
	*line = *str ? *str : gnl_strndup("", 1);
	*str = NULL;
	if (*line == NULL)
		return (handle_error(str, buf));
	return (handle_success(DONE, buf));
}

static void	append_to_string(char **str, char *buf, int n)
{
	char *tmp;

	buf[n] = '\0';
	if (*str == NULL)
		*str = gnl_strndup(buf, n);
	else
	{
		tmp = gnl_strjoin(*str, buf);
		free(*str);
		*str = tmp;
	}
}

int			get_next_line(int fd, char **line)
{
	static char	*str;
	char		*buf;
	int			n;
	char		*nl;

	n = 0;
	nl = NULL;
	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (ERROR);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ERROR);
	while ((nl = gnl_strchr(str, '\n')) == NULL &&
			(n = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		append_to_string(&str, buf, n);
		if (str == NULL)
			return (handle_error(&str, &buf));
	}
	if (n == -1)
		return (handle_error(&str, &buf));
	return (newline_or_eof(line, &str, nl, &buf));
}
