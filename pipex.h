#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#include "get_next_line.h"
#include "ft_printf.h"

typedef struct child
{
	char	**cmd;
	int		fd;
	int		exec;
	char	**all_path;
	char	*path;
}	t_child;

//pipex.c
void	child(char **argv,int *pipe_fd, char **env);
int		parent(char **argv,int *pipe_fd, char **env);

//lib.c
int		len(char *s);
char	*ft_strjoin3(char const *s1, char const *s2);
char	*ft_strdup2(const char *s1);
int		ft_atoi(const char *str);

//utils.c
void	print_2c(char **c);
void	error(int i);
void	error2(int i);
void	read_infile(char **argv);

//path.c
char	**get_path(char **env);

//autre
char	**ft_split(char const *s, char c);

#endif
