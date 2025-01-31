#include "pipex.h"

void	print_2c(char **c)
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
		write(1, "/", 1);
		write(1, "\n", 1);

	i++;
	}
		write(1, c[i], j);
		write(1, "/", 1);
		write(1, "\n", 1);
}

void error(void)
{
	exit(EXIT_FAILURE);
}
