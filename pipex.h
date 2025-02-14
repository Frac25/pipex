/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydubois <sydubois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:49:08 by sydubois          #+#    #+#             */
/*   Updated: 2025/02/14 15:32:45 by sydubois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>

# include "get_next_line.h"
# include "ft_printf.h"

typedef struct pip
{
	char	**cmd;
	char	**all_path;
}	t_pip;

typedef struct p
{
	int	j;
	int	sta;
	int	fd_first;
	int	fd_last;
}	t_pipex;

//pipex.c
void	child(char **argv, int *pipe_fd, char **env, int j);
int		parent(char **argv, int *pipe_fd, char **env);

//lib.c
int		len(char *s);
char	*ft_strdup2(const char *s1);
int		ft_atoi(const char *str);
int		strlen_2(char **str);
int		ft_same_str(char *s1, char *s2);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3);

//utils.c
void	print_2c(char **c);
void	error(int i);
void	error2(int i);
void	error20(int i, char **cmd);
void	error10(int i, char *c);

//void	read_infile(char **argv);
void	free2(char **c);

//path.c
char	**get_path(char **env);

//heredoc.c
int		detect_hd(char **argv);

//autre
char	**ft_split(char const *s, char c);

#endif
