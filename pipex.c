#include "pipex.h"

int parent(char **argv)
{
	int fd1;
//	ssize_t nb_read;

	printf("file 2 = %s\n", argv[4]);
	printf("commande 2  = %s\n", argv[3]);

	fd1 = open(argv[1], O_RDONLY);
	if ( fd1 == -1)
		printf("erreur open \n");


	close(fd1);

	return (0);
}

int child(char **argv,int *pipe_fd, char **env)
{
	int fd;
///	void *file;
//	ssize_t nb_read;
	char **path;

	printf("file 1 = %s\n", argv[1]);
	printf("commande 1  = %s\n\n", argv[2]);

	fd = open(argv[1], O_RDONLY);
	if ( fd == -1)
		printf("erreur open \n");

	printf("\nle contenu de file est : %s\n", get_next_line(fd));
	printf("\nle contenu de file est : %s\n", get_next_line(fd));
	printf("\nle contenu de file est : %s\n", get_next_line(fd));

//	write(1, "\nenv = \n\n", 9);
//	print_2c(env);
//	printf("\n\n");

	path = NULL;
	path = get_path(env);
//	printf("path 1 = %s\n", path[0]);
	printf("je dois appliquer la commande 1 !\n\n");

	int ex;
	int i;
	char **fct; // = {"ls", NULL};

//	fct = NULL;
	fct = malloc(sizeof(char*)*100);
	fct[0] = ft_strdup2(argv[2]);
	fct[1] = ft_strdup2("-l");
	fct[2] = NULL;

	char *path3;
	i = 0;
	ex = -1;
	while (ex == -1 && path[i] != NULL)
	{
		path3 = ft_strjoin3(path[i], "/");
		path3 = ft_strjoin3(path3, argv[2]);

		ex = execve(path3, fct, env);
//		printf("path = %s et fct[0] = %s, et ex = %d\n", path3, fct[0],ex);
		i++;
	}
	printf("a priori on ne passe pas la");

///	je renvoie dans un fichier tampo


	close(fd);
	return (0);
}



int main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];

	int * stat_loc;
	stat_loc = NULL;
	pid = 0;
	if (argc != 5)
	{
		printf("erreur, argc = %d\n", argc);
		error();
	}
	if (pipe(pipe_fd) == -1)
	{
		printf("erreur, pipe = %d\n", pid);
		error();
	}
//	printf("pipe[0] = %d et pipe[1] = %d\n", pipe_fd[0], pipe_fd[1]);
	pid = fork();
	if (pid == -1)
	{
		printf("erreur, pid = %d\n", pid);
		error();
	}
	else if (pid != 0) //pere
	{
		printf("je suis le pere, mon fils est au %d\n", pid);
		printf("je suis le pere, j ecrit un message dans le pipe[1] = %d\n", pipe_fd[1]);
//		close(pipe_fd[0]);
		int a;
		a = write (pipe_fd[1], "mess  e secret\0", 15);
		printf("\nja suis le pere, le nd de message secret est : %d\n", a);
		printf("\nja suis le pere, j'attends le fils\n");
		waitpid(pid, stat_loc, 0);
		printf("\nja suis le pere, j'ai attendu la fin du fils\n");
//		parent(argv);

	}
	else //child
	{
		sleep(1);
		printf("\nje suis le fils, pid = %d\n", pid);
//		close(pipe_fd[1]);

		char buf[15];
		int r;
		r = read(pipe_fd[0], buf, 15);
		if (r == -1)
			printf("pb read fils\n");
		printf(" message = %s\n", buf);

//	char	*message;

//	printf (" get_next_line(3) = %s\n", get_next_line(3));


//	printf ("pipe_fd[0] = %d\n", pipe_fd[0]);
//	message = get_next_line(pipe_fd[0]);
//	printf (" get_next_line(pipe_fd[0]) = %s\n", message);

		child(argv, pipe_fd, env);

	}
	return(0);
}
