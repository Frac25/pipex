#include "pipex.h"

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
		write(1, "/", 1);
		write(1, "\n", 1);

	i++;
	}
		write(1, c[i], j);
		write(1, "/", 1);
		write(1, "\n", 1);
}

void error(int i)
{
	if ( i == 0)
		exit(EXIT_SUCCESS);
	else if(i == 1)
		exit(EXIT_FAILURE);
	else if(i == 10)
	{
		ft_printf("pipex file1 cmd1 cmd2 file2\n");
		exit(EXIT_SUCCESS);
	}
	else if(i == 11)
	{
		ft_printf("erreur pipe");
		exit(EXIT_FAILURE);
	}
	else if(i == 12)
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
	else if(i == 21)
	{
		ft_printf("pas de chemin trouvé pour la cmd\n");
		exit(EXIT_FAILURE);
	}
	else if(i == 22)
	{
		ft_printf("erreur malloc\n");
		exit(EXIT_FAILURE);
	}
	else if(i == 23)
	{
		ft_printf("erreur dup2\n");
		exit(EXIT_FAILURE);
	}
}

void read_infile(char **argv)
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
