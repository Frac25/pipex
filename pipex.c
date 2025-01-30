#include "pipex.h"

int	len(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin3(char const *s1, char const *s2)
{
	char		*c;
	size_t		i;
	size_t		j;

	if (s1 && s2)
	{
		c = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (c == NULL)
			return (NULL);
		i = 0;
		while (i < ft_strlen(s1))
		{
			c[i] = s1[i];
			i++;
		}
		j = 0;
		while (j < ft_strlen(s2))
			c[i++] = s2[j++];
		c[i] = '\0';
		return (c);
	}
	return (NULL);
}

char	*ft_strdup2(const char *s1)
{
	int		i;
	char	*c;

	c = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (c == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		c[i] = s1[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}

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
		write(1, "\n", 1);

	i++;
	}
}

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

	printf("le contenu de file est : %s", get_next_line(fd));
	printf("le contenu de file est : %s", get_next_line(fd));
	printf("le contenu de file est : %s", get_next_line(fd));

//	write(1, "\nenv = \n\n", 9);
//	print_2(env);
//	printf("\n\n");

	path = NULL;
	path = get_path(env);

	printf("path 1 = %s\n", path[0]);

	printf("je dois appliquer la commande 1 !\n\n");

	int ex;
	int i;
	char **fct; // = {"ls", NULL};

//	fct = NULL;
	fct = malloc(sizeof(char*)*100);
	fct[0] = ft_strdup2(argv[2]);
	fct[1] = ft_strdup2("-l");
	fct[2] = NULL;
	printf("fct[0] = %s\n", fct[0]);
	printf("fct[1] = %s\n", fct[1]);


	char *path3;
	i = 0;
	ex = -1;

	path3 = ft_strjoin3("/usr/bin", "/ls");
	ex = execve(path3, fct, env);
	printf("path = %s et fct[0] = %s, et ex = %d\n", path3, fct[0],ex);

	path3 = ft_strjoin3("/bin", "/ls");
	ex = execve(path3, fct, env);
	printf("path = %s et fct[0] = %s, et ex = %d\n", path3, fct[0],ex);



	while (ex == -1 && path[i] != NULL)
	{
		path3 = ft_strjoin3(path[i], "/");
		path3 = ft_strjoin3(path3, argv[2]);

//		ex = execve(path3, fct, env);
		printf("path = %s et fct[0] = %s, et ex = %d\n", path3, fct[0],ex);
		i++;
	}


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

	stat_loc = NULL;
	pid = 0;

//	printf("argc = %d\n", argc);
//	write(1, "argv = ", 7);
//	print_2(argv);
//	write(1, "\nenv = ", 7);
//	print_2(env);
//	printf("\n\n");
//	write(1, env[0], 2);
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
//		parent(argv);

	}
	else //child
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

		child(argv, pipe_fd, env);

	}
	return(0);
}
