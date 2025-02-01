#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		*stat_loc;

	pid = 0;
	stat_loc = NULL;
	if (argc != 5)
		error(10);
	if (pipe(pipe_fd) == -1)
		error(11);
	pid = fork();
	if (pid == -1)
		error(12);
	else if (pid != 0) //parent
	{
		printf("je suis le pere, mon fils est au %d, j'attends qu'il termine\n", pid);
		waitpid(pid, stat_loc, 0);
		sleep(2);
		printf("\nje suis le pere, j'ai attendu la fin du fils\n");
		parent(argv, pipe_fd, env);
		return(0);
	}
	else //child
		child(argv, pipe_fd, env);
	return(0);
}

void child(char **argv,int *pipe_fd, char **env)
{
	t_child	*p;
	int		i;
	int testdup;

	p = malloc(sizeof(t_child*));
	if(p == NULL)
		error(22);
	sleep(10);
	ft_printf("\nje suis le fils, pid = ?, file 1 = %s, commande 1  = %s\n",  argv[1], argv[2]);
	p->cmd = ft_split(argv[2], ' ');
	p->fd = open(argv[1], O_RDONLY);
	if (p->fd == -1)
		error(20);
	printf(" p->fd = %d\n", p->fd);

	sleep(10);

	if(dup2(p->fd, 0) == -1)
		error(23);
	sleep(10);
	printf(" pipe_fd[1] = %d\n", pipe_fd[1]);
	testdup = dup2(pipe_fd[1], 1);
	printf("testdup = %d", testdup);
	sleep(10);
//	printf("dup2(p->fd, 0) = %d\n", dup2(p->fd, 0));
//	dup2(p->fd, 0);

//	printf(" pipe_fd[1] = %d\n", pipe_fd[1]);
//	write(1, "tes0", 4);
//	dup2(pipe_fd[1], 1);
//	printf("dup2(pipe_fd[1], 1) = %d\n", dup2(pipe_fd[1], 1));
	write(1, "test\n", 5);
	i = 0;
/*	printf(" pipe_fd[0] = %d\n", pipe_fd[0]);
	close(pipe_fd[0]);
	p->exec = -1;
	p->all_path = get_path(env);

	while (p->exec == -1 && p->all_path[i] != NULL)
	{
		p->path = ft_strjoin3(p->all_path[i], "/");
		p->path = ft_strjoin3(p->path, p->cmd[0]);
		p->exec = execve(p->path, p->cmd, env);
		i++;
	}
*/
	error(21);
}

int parent(char **argv,int *pipe_fd, char **env)
{
	int fd;
	char **path; // /bin    /bin/toto
	char *path2; // /bin/wc
	char **cmd; // {wc, -l, NULL}
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
	cmd = ft_split(argv[3], ' ');
	path = get_path(env);
	i = 0;
	ex = -1;
	while(ex == -1)
	{
		path2 = ft_strjoin3(path[i], "/");
		path2 = ft_strjoin3(path2, cmd[0]);
		ex = execve(path2, cmd, env);
		i++;
	}
	close(fd);

	return (0);
}

