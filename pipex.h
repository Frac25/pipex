#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "get_next_line.h"

//lib.c
int		len(char *s);
char	*ft_strjoin3(char const *s1, char const *s2);
char	*ft_strdup2(const char *s1);

//utils.c
void	print_2c(char **c);
void	error(void);

//path.c
char	**get_path(char **env);

//autre
char	**ft_split(char const *s, char c);

#endif
