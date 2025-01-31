/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42Lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:57:33 by sydubois          #+#    #+#             */
/*   Updated: 2025/01/31 12:43:25 by sydubois         ###   ########.fr       */
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
	write(1,"t00",3);
	while (i == -1)
	{
		buf_short = ft_buffer(fd, error);
		if (*error != 0)
		{
			free(seq);
			write(1,"t10",3);
			return (NULL);
		}
		if (buf_short == NULL)
		{
			write(1,"t20",3);
			return (seq);

		}
		write(1,"t30",3);
		buf_long = ft_strjoin2(seq, buf_short);
		write(1,"t40 ",4);
		seq = buf_long;
		i = chr_start(seq, '\n');
		write(1,&i,2);
		write(1," t50 ",5);
		write(1,&i,2);
	}
	write(1,"t60",3);
	return (seq);
}

char	*get_next_line(int fd)
{
	char		*seq_s;
	char		*seq_l;
	char		*line;
	static char	*rest;
	int			error;

	write(1,"t",1);
	printf("passe 0");
	error = 0;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > 10240)
	{
		write(1,"t2",2);
		return (NULL);
	}
	seq_s = NULL;
	if (rest == NULL || chr_start(rest, '\n') == -1)
	{
		write(1,"t3",2);
		seq_s = sequence(fd, &error);
	}
	printf("passe 0.5");
	write(1,"t4",2);
	if (error != 0)
	{
		free(rest);
		rest = NULL;
	}
	if (rest == NULL && seq_s == NULL)
		return (NULL);
	printf("passe 1");
	seq_l = ft_strjoin2(rest, seq_s);
	line = ft_substr(seq_l, 0, chr_start(seq_l, '\n'));
	rest = ft_substr(seq_l, chr_start(seq_l, '\n'), chr_rest(seq_l, '\n'));
	free(seq_l);
	return (line);
}
