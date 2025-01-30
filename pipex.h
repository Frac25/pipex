#ifndef PIPEX_H
# define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "get_next_line.h"

char	**ft_split(char const *s, char c);
char	**get_path(char **env);

#endif
