/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:50:56 by sydubois          #+#    #+#             */
/*   Updated: 2025/02/13 18:44:50 by sydubois         ###   ########.fr       */
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
		if(access(path, R_OK) != -1)
			break ;
		i++;
		free(path);
		path = NULL;
	}
	if	(path == NULL)
	{
//		free2(cmd);
		free2(all_path);
		error10(101, cmd[0]);
	}
	if (execve(path, cmd, env) == -1)
	{
		free(path);
//		free2(cmd);
		free2(all_path);
		error10(101, cmd[0]);
	}
}

int	pipe_j(char **cmd, char **all_path, char **env)
{
	int		pip[2];
	pid_t	pid;
	int		stat_loc;
	int		exit_stat;

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
	exit_stat = 0;
	if(WIFEXITED(stat_loc))
	exit_stat = WEXITSTATUS(stat_loc);
//	printf("exit_stat = %d\n", exit_stat);
	return(exit_stat);
}

int	pipe_last(char **cmd, char **all_path, char **env, int fd_last)
{
	pid_t	pid;
	int		stat_loc;
	int		exit_stat;

	pid = fork();
	if (pid == 0)
	{
		dup2(fd_last, 1);
		exec_cmd(cmd, all_path, env);
	}
	waitpid(pid, &stat_loc, 0);
	exit_stat = 0;
	if(WIFEXITED(stat_loc))
		exit_stat = WEXITSTATUS(stat_loc);
//	printf("exit_stat = %d\n", exit_stat);
	return(exit_stat);
}

int	main(int argc, char **argv, char **env)
{
	int		j;
	int		fd_first;
	int		fd_last;
	char	**all_path;
	int		sta;
	char	**split;

	j = 0;
	if (argc < 5)
		error(10);
	
	if (detect_hd(argv) == 1)
	{
		fd_first = open("tmp_file.txt", O_RDONLY);
		j += 1;
	}
	else
	{
		if (access(argv[1], R_OK) != -1)
			fd_first = open(argv[1], O_RDONLY);
		else
			error10(100, argv[1]);
	}
//	if (access(argv[argc -1], R_OK) != -1)
		fd_last = open(argv[argc -1], O_WRONLY | O_TRUNC | O_CREAT , 0777);
//	else
//		error10(100, argv[argc -1]);
	dup2(fd_first, 0);
	all_path = get_path(env);
	j += 2;
	while (j < argc - 2)
	{
		split = ft_split(argv[j++], ' ');
		pipe_j(split, all_path, env);
		free(split);
	}
	sta = 0;
	split = ft_split(argv[j], ' ');
	pipe_last(split, all_path, env, fd_last);
	free(split);
	free2(all_path);
	return (sta);
}
