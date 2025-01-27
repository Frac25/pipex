#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

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
	i++;
	}
}

int main(int argc, char **argv, char **env)
{
	int	pid;

	printf("argc = %d\n", argc);
	write(1, "argv = ", 7);
	print_2(argv);
	write(1, "\nenv = ", 7);
	print_2(env);
	printf("\n\n");


	pid = fork();
	if (pid == -1)
	{
	printf("erreur, pid = %d\n", pid);
	}
	else if (pid == 0)
	{
	printf("ja suis le fils, pid = %d\n", pid);
	}
	else{
	printf("ja suis le pere, mon fils est au %d\n", pid);
	}


	return(0);
}
