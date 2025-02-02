#include "pipex.h"

void exec_cmd(char **cmd, char **all_path, char **env)
{
	int		exec;
	int		i;
	char	*path;

	exec = -1;
	i = 0;
	while (exec == -1 && all_path[i] != NULL)
	{
		path = ft_strjoin3(all_path[i], "/");
		path = ft_strjoin3(path, cmd[0]);
//		printf("\naccess = %d\n", access(path, F_OK | X_OK));
//		printf("path = %s\n", path);
		exec = execve(path, cmd, env);
		i++;
	}
	write(2, "zsh: command not found: ", 24);
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, "\n",1);
	error(21);
}

void pipe_j(char **cmd, char **all_path, char **env)
{
	int		pip[2];
	pid_t	pid;

	pipe(pip);
	pid = fork();
	if(pid == 0) // child
	{
		dup2(pip[1], 1);
		close(pip[0]);
		exec_cmd(cmd, all_path, env);
	}
	else // parent
	{
//		wait(pid, stat_loc, 0);
		dup2(pip[0], 0);
		close(pip[1]);
	}
}

int main(int argc, char **argv, char **env)
{
	int j;
	int fd_first;
	int fd_last;
	char **all_path;


	if (argc < 5)
		error(10);
	all_path = get_path(env);
	fd_first = open(argv[1], O_RDONLY);
	fd_last = open(argv[argc -1], O_WRONLY | O_TRUNC);
	dup2(fd_first, 0);
	j = 2;
	while(j < argc - 2)
		pipe_j(ft_split(argv[j++], ' '), all_path, env);
	dup2(fd_last, 1);
	exec_cmd(ft_split(argv[j], ' '), all_path, env);
	return(0);
}



