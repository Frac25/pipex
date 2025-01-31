#include "pipex.h"

void read_infile(char **argv)
{
	int fd;

	fd = open(argv[1], O_RDONLY);
	if ( fd == -1)
		printf("erreur open \n");
	printf("le contenu de file est : %s", get_next_line(fd));
	printf("le contenu de file est : %s", get_next_line(fd));
	printf("le contenu de file est : %s", get_next_line(fd));
	close(fd);
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
	pid = fork();
	if (pid == -1)
	{
		printf("erreur, pid = %d\n", pid);
		error();
	}
	else if (pid != 0) //parent
	{
		printf("je suis le pere, mon fils est au %d\n", pid);
		printf("\nja suis le pere, j'attends le fils\n");
		waitpid(pid, stat_loc, 0);
		printf("\nja suis le pere, j'ai attendu la fin du fils\n");
		parent(argv, pipe_fd, env);
	}
	else //child
		child(argv, pipe_fd, env);
	return(0);
}

int child(char **argv,int *pipe_fd, char **env)
{

///	void *file;
//	ssize_t nb_read;
	char **path;
	int ex;
	int i;
	char **fct; // = {"ls", "-l", NULL};
	char *path3; // = /bin/l

	sleep(1);
	printf("\nje suis le fils, pid = 0\n");
	printf("file 1 = %s\n", argv[1]);
	printf("commande 1  = %s\n\n", argv[2]);

	fct = ft_split(argv[2], ' ');


	int fd;
	fd = open(argv[1], O_RDONLY);
	if ( fd == -1)
		printf("erreur open \n");
/// je change la source de 'stdin' a 'infile'
	dup2(fd, 0);
///	je change la source de std out a pipe[1]
	dup2(pipe_fd[1], 1);


//	int fd2;
//	fd2 = open(argv[4], O_RDONLY);
//	if ( fd2 == -1)
//		printf("erreur open \n");
//	dup2(fd2, 1);

	close(pipe_fd[0]);
	i = 0;
	ex = -1;
	path = get_path(env);
	while (ex == -1 && path[i] != NULL)
	{
		path3 = ft_strjoin3(path[i], "/");
		path3 = ft_strjoin3(path3, fct[0]);
		ex = execve(path3, fct, env);
//		printf("path = %s et fct[0] = %s, et ex = %d\n", path3, fct[0],ex);
		i++;
	}
	printf("a priori on ne passe pas la");
	return (0);
}

int parent(char **argv,int *pipe_fd, char **env)
{
	int fd;
	char **path; // /bin    /bin/toto
	char *path2; // /bin/wc
	char **fct; // {wc, -l, NULL}
	int i;
	int ex;

	printf("file 2 = %s\n", argv[4]);
	printf("commande 2  = %s\n", argv[3]);
	fd = open(argv[4], O_WRONLY);
	if ( fd == -1)
		printf("erreur open \n");
	dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
	fct = ft_split(argv[3], ' ');
	path = get_path(env);
	i = 0;
	ex = -1;
	while(ex == -1)
	{
		path2 = ft_strjoin3(path[i], "/");
		path2 = ft_strjoin3(path2, fct[0]);
		ex = execve(path2, fct, env);
		i++;
	}
	close(fd);

	return (0);
}

