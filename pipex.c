/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:50:56 by sydubois          #+#    #+#             */
/*   Updated: 2025/02/14 16:51:27 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(char **cmd, char **all_path, char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (all_path[i] != NULL)
	{
		path = ft_strjoin3(all_path[i], "/", cmd[0]);
		if (access(path, R_OK) != -1)
			break ;
		i++;
		free(path);
		path = NULL;
	}
	if (path == NULL)
	{
		free2(all_path);
		error20(101, cmd);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
		free2(all_path);
		error20(101, cmd);
	}
}

int	pipe_j(char *arg, char **all_path, char **env)
{
	int		pip[2];
	pid_t	pid;
	int		stat_loc;
	int		exit_stat;
	char	**cmd;

	if (arg[0] == '\0')
		return (0);
	cmd = ft_split(arg, ' ');
	pipe(pip);
	pid = fork();
	if (pid == 0)
	{
		dup2(pip[1], 1);
		close(pip[0]);
		exec_cmd(cmd, all_path, env);
	}
	dup2(pip[0], 0);
	close(pip[1]);
	waitpid(pid, &stat_loc, 0);
	free2(cmd);
	exit_stat = 0;
	if (WIFEXITED(stat_loc))
		exit_stat = WEXITSTATUS(stat_loc);
	return (exit_stat);
}

int	pipe_last(char *arg, char **all_path, char **env, int fd_last)
{
	pid_t	pid;
	int		stat_loc;
	int		exit_stat;
	char	**cmd;

	if (arg[0] == '\0')
		return (0);
	cmd = ft_split(arg, ' ');
	if (cmd == NULL)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd_last, 1);
		exec_cmd(cmd, all_path, env);
	}
	waitpid(pid, &stat_loc, 0);
	exit_stat = 0;
	free2(cmd);
	if (WIFEXITED(stat_loc))
		exit_stat = WEXITSTATUS(stat_loc);
	return (exit_stat);
}

int	open_infile(char *arg)
{
	int	fd;

	printf("access in = %d", access(arg, R_OK));
	if (access(arg, R_OK) != -1)
	{
		fd = open(arg, O_RDONLY);
	}
	else
		error10(100, arg);
	return (fd);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	p;
	int		j;
	char	**all_path;

	j = 2;
	if (argc < 5)
		error(10);
	if (detect_hd(argv) == 1)
	{
		p.fd_first = open("tmp_file.txt", O_RDONLY);
		j++;
	}
	else
		p.fd_first = open_infile(argv[1]);
//	printf("access last = %d", access(argv[argc -1], R_OK));
	p.fd_last = open(argv[argc -1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	dup2(p.fd_first, 0);
	all_path = get_path(env);
	while (j < argc - 2)
		pipe_j(argv[j++], all_path, env);
	p.sta = 0;
	p.sta = pipe_last(argv[j], all_path, env, p.fd_last);
	if(access(argv[argc -1], R_OK) == -1)
		p.sta = 1;
	free2(all_path);
	return (p.sta);
}
