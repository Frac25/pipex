#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		*stat_loc;
	int		s;


	pid = 0;
	stat_loc = NULL;
	if (argc != 6)
		error(10);
	s = ft_atoi(argv[5]);
	if (pipe(pipe_fd) == -1)
		error(11);
	pid = fork();
	if (pid == -1)
		error(12);
	else if (pid != 0) //parent
	{

		printf("je suis le pere au %d, mon fils est au %d, j'attends qu'il termine\n", getpid(), pid);
		waitpid(pid, stat_loc, 0);
		printf("\nje suis le pere, j'ai attendu la fin du fils\n");
		parent(argv, pipe_fd, env);
		return(0);
	}
	else //child
		child(argv, pipe_fd, env, s);
	return(0);
}

void child(char **argv,int *pipe_fd, char **env, int s)
{
	t_child	*p;
	int		i;
	char	**cmd;
	char	**all_path;
	char	*path;

	p = malloc(sizeof(t_child*));
	if(p == NULL)
		error(22);
	sleep(1);
	ft_printf("\nje suis le fils, pid = ?, file 1 = %s, commande 1  = %s\n",  argv[1], argv[2]);
	cmd = ft_split(argv[2], ' ');
	p->fd = open(argv[1], O_RDONLY);
	if (p->fd == -1)
		error(20);
	printf("p->fd = %d\n", p->fd);
	if(dup2(p->fd, 0) == -1)
		error(23);
	if (s == 4)
	{
		if(dup2(pipe_fd[1], 1) == -1)
			error(23);
	}
	close(pipe_fd[0]);
	i = 0;
	p->exec = -1;
	all_path = get_path(env);
	while (p->exec == -1 && all_path[i] != NULL)
	{
		path = ft_strjoin3(all_path[i], "/");
		path = ft_strjoin3(path, cmd[0]);
//		printf("\naccess = %d\n", access(path, F_OK | X_OK));
//		printf("path = %s\n", path);
		p->exec = execve(path, cmd, env);
		i++;
	}
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
	fd = open(argv[4], O_WRONLY | O_TRUNC);
	if ( fd == -1)
		printf("erreur open \n");
	cmd = ft_split(argv[3], ' ');
	path = get_path(env);
	i = 0;
	ex = -1;
		dup2(fd, 1);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[1]);
//	perror(get_next_line(0));
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

