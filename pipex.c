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

int parent(char **argv)
{
	int fd1;
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







	printf("je dois appliquer la commande 1\n\n");

///	je renvoie dans un fichier tampo


	close(fd);
	return (0);
}

void error(void)
{
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	int * stat_loc;

//	printf("argc = %d\n", argc);
//	write(1, "argv = ", 7);
//	print_2(argv);
//	write(1, "\nenv = ", 7);
//	print_2(env);
//	printf("\n\n");
	if (argc != 5)
	{
		printf("erreur, argc = %d\n", pid);
		error();
	}

	if (pipe(pipe_fd) == -1)
	{
		printf("erreur, pipe = %d\n", pid);
		error();
	}
	printf("pipe[0] = %d et pipe[1] = %d\n", pipe_fd[0], pipe_fd[1]);


	pid = fork();
	if (pid == -1)
	{
		printf("erreur, pid = %d\n", pid);
		error();
	}
	else if (pid != 0) //pere
	{
		printf("ja suis le pere, mon fils est au %d\n", pid);
		printf("ja suis le pere, j ecrit un message dans le pipe[0]\n");
		close(pipe_fd[0]);
		write (pipe_fd[1], "message secret\0", 15);

		waitpid(pid, stat_loc, 0);
		printf("\nja suis le pere, j'ai attendu la fin du fils\n");
		parent(argv);

	}
	else
	{
		sleep(1);
		printf("\nje suis le fils, pid = %d\n", pid);
		printf("\nje suis le fils,");
		close(pipe_fd[1]);

		char buf[15];
		int r;
		r = read(pipe_fd[0], buf, 15);
		if (r == -1)
			printf("pb read fils\n");
		printf(" message = %s", buf);

//		child(argv);

	}



	return(0);
}
