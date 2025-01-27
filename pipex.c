#include "pipex.h"

void	print_2(char **c)
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
		write(1, " ", 1);

	i++;
	}
}
/*
size_t strlen_st(void *v)
{
	int	i;

	i = 0;
	while (v[i] != 0)
	{
		i++;
	}
	return(i);
}
*/

int parent(char **argv)
{
	int fd1;
///	void *file;
	ssize_t nb_read;

	printf("file 2 = %s\n", argv[4]);
	printf("commande 2  = %s\n", argv[3]);

	fd1 = open(argv[1], O_RDONLY);
	if ( fd1 == -1)
		printf("erreur open \n");

	close(fd1);
	return (0);
}

int child(char **argv)
{
	int fd;
///	void *file;
	ssize_t nb_read;

	printf("file 1 = %s\n", argv[1]);
	printf("commande 1  = %s\n\n", argv[2]);

	fd = open(argv[1], O_RDONLY);
	if ( fd == -1)
		printf("erreur open \n");

	printf("le contenu de file est : %s", get_next_line(fd));
	printf("le contenu de file est : %s", get_next_line(fd));
	printf("le contenu de file est : %s", get_next_line(fd));

	printf("je dois appliquer la commande 1");

	je renvoie dans un fichier tampo


	close(fd1);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	int	pid;

	int * stat_loc;

//	printf("argc = %d\n", argc);
//	write(1, "argv = ", 7);
//	print_2(argv);
//	write(1, "\nenv = ", 7);
//	print_2(env);
//	printf("\n\n");

	pid = fork();
	if (pid == -1)
		printf("erreur, pid = %d\n", pid);
	else if (pid != 0)
	{
		printf("ja suis le pere, mon fils est au %d\n", pid);

		waitpid(pid, stat_loc, 0);
		printf("ja suis le pere, jái attendu la fin du fils\n");
		parent(argv);

	}
	else
	{
		sleep(1);
		printf("\nje suis le fils, pid = %d\n", pid);

		child(argv);

	}



	return(0);
}
