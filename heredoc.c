/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:57:28 by sydubois          #+#    #+#             */
/*   Updated: 2025/02/17 12:48:59 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	detect_hd(char **argv)
{
	char	*limiter;
	int		fd;
	char	*line;

	if (ft_same_str(argv[1], "here_doc") == 1)
	{
		limiter = argv[2];
		fd = open("tmp_file.txt", O_CREAT | O_TRUNC | O_WRONLY, 0777);
		while (1)
		{
			write(1, ">", 1);
			line = get_next_line(STDIN_FILENO);
			if (ft_strcmp(limiter, line) == 0)
				break ;
			else
				write(fd, line, ft_strlen(line));
			free(line);
		}
		free(line);
		free(limiter);
		close(fd);
		return (1);
	}
	return (0);
}
