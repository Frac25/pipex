/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42Lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:57:33 by sydubois          #+#    #+#             */
/*   Updated: 2025/01/31 13:06:33 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

static char	*ft_buffer(int fd, int *error)
{
	char	*buf_raw;
	int		read_out;
	size_t	i;

	buf_raw = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf_raw == NULL)
		return (NULL);
	i = 0;
	while (i < (sizeof(char) * (BUFFER_SIZE + 1)))
		buf_raw[i++] = 0;
	read_out = read(fd, buf_raw, BUFFER_SIZE);
	if (read_out <= 0)
	{
		*error = read_out;
		free(buf_raw);
		buf_raw = NULL;
	}
	return (buf_raw);
}

static char	*sequence(int fd, int *error)
{
	char	*buf_short;
	char	*buf_long;
	char	*seq;
	int		i;

	seq = NULL;
	i = -1;
	while (i == -1)
	{
		buf_short = ft_buffer(fd, error);
		if (*error != 0)
		{
			free(seq);
			return (NULL);
		}
		if (buf_short == NULL)
			return (seq);
		buf_long = ft_strjoin2(seq, buf_short);
		seq = buf_long;
		i = chr_start(seq, '\n');
	}
	return (seq);
}

char	*get_next_line(int fd)
{
	char		*seq_s;
	char		*seq_l;
	char		*line;
	static char	*rest;
	int			error;

	error = 0;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 10240)
		return (NULL);
	seq_s = NULL;
	if (rest == NULL || chr_start(rest, '\n') == -1)
		seq_s = sequence(fd, &error);
	if (error != 0)
	{
		free(rest);
		rest = NULL;
	}
	if (rest == NULL && seq_s == NULL)
		return (NULL);
	seq_l = ft_strjoin2(rest, seq_s);
	line = ft_substr(seq_l, 0, chr_start(seq_l, '\n'));
	rest = ft_substr(seq_l, chr_start(seq_l, '\n'), chr_rest(seq_l, '\n'));
	free(seq_l);
	return (line);
}
