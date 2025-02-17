/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 10:27:55 by sydubois          #+#    #+#             */
/*   Updated: 2025/02/17 12:05:16 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int i)
{
	if (i == 0)
		exit(EXIT_SUCCESS);
	else if (i == 1)
		exit(EXIT_FAILURE);
	else if (i == 10)
	{
		ft_printf("pipex file1 cmd1 cmd2 file2\n");
		exit(EXIT_SUCCESS);
	}
	else if (i == 11)
	{
		ft_printf("erreur pipe");
		exit(EXIT_FAILURE);
	}
	else if (i == 12)
	{
		ft_printf("erreur fork");
		exit(EXIT_FAILURE);
	}
	else
		error2(i);
	exit(EXIT_FAILURE);
}

void	error2(int i)
{
	if (i == 20)
	{
		ft_printf("erreur open \n");
		exit(EXIT_FAILURE);
	}
	else if (i == 21)
	{
		exit(EXIT_FAILURE);
	}
	else if (i == 22)
	{
		ft_printf("erreur malloc\n");
		exit(EXIT_FAILURE);
	}
	else if (i == 23)
	{
		ft_printf("erreur dup2\n");
		exit(EXIT_FAILURE);
	}
}

void	error10(int i, char *c)
{
	if (i == 100)
	{

		write(2, "zsh: no such file or directory: ", 32);
		write(2, c, ft_strlen(c));
		write(2, "\n", 1);
		exit(EXIT_SUCCESS);
	}
	if (i == 101)
	{
		dprintf(2, "zsh: %s: %s", strerror(errno), c);
		exit(EXIT_SUCCESS);
	}
	else
		ft_printf("erreur de message d ereur");
}

void	error20(int i, char **arg)
{
	if (i == 100)
	{
		write(2, "zsh: no such file or directory: ", 32);
		write(2, arg[0], ft_strlen(arg[0]));
		write(2, "\n", 1);
		free2(arg);
		exit(EXIT_SUCCESS);
	}
	else if (i == 101)
	{
		write(2, "zsh: command not found: ", 24);
		write(2, arg[0], ft_strlen(arg[0]));
		write(2, "\n", 1);
		free2(arg);
		exit(EXIT_FAILURE);
	}
	else
		ft_printf("erreur de message d ereur");
}
//zsh: permission denied: outfile_na
void	free2(char **c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		free(c[i]);
		i++;
	}
	free(c);
}
/*

void	print_2c(char **c)
{
	int	i;
	int	j;

	i = 0;
	while (c[i])
	{
		j = 0;
		while (c[i][j])
		{
			j++;
		}
		write(1, c[i], j);
		write(1, "\n", 1);
		i++;
	}
	write(1, c[i], j);
	write(1, "\n", 1);
}

void	read_infile(char **argv)
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	if ( fd == -1)
	printf("erreur open \n"); //attention printf interdit
	printf("le contenu de file est : %s", get_next_line(fd));
	printf("le contenu de file est : %s", get_next_line(fd));
	printf("le contenu de file est : %s", get_next_line(fd));
	close(fd);
}
*/