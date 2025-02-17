/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:27:12 by sydubois          #+#    #+#             */
/*   Updated: 2025/02/17 12:36:26 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	search_env(char *title, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0' && title[j] != '\0' && env[i][j] == title[j])
		{
			j++;
			if (title[j] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	**get_path(char **env)
{
	char	*path;
	char	**path2;
	int		line;

	line = search_env("PATH", env);
	path = ft_strdup2(env[line]);
	path2 = ft_split(path, '=');
	free(path);
	path = ft_strdup2(path2[1]);
	free2(path2);
	path2 = ft_split(path, ':');
	free(path);
	return (path2);
}

int	open_infile(char *arg)
{
	int	fd;

	if (access(arg, R_OK) != -1)
		fd = open(arg, O_RDONLY);
	else
	{
		dprintf(2, "zsh: %s: %s", strerror(errno), arg);
		exit(EXIT_SUCCESS);
	}
	return (fd);
}

int	open_outfile(char *arg)
{
	int	fd;

	fd = open(arg, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (access(arg, W_OK) == -1)
	{
		dprintf(2, "zsh: %s: %s", strerror(errno), arg);
		exit(EXIT_SUCCESS);
	}
	return (fd);
}
