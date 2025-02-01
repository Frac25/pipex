#include "pipex.h"

char	**get_path(char **env)
{
	char	*path;
	char	**path2;
	int		i;

	i = 0;
	path = NULL;
	while (env[4][i + 5] != '\0')
		i++;
	path = malloc(sizeof(char*) * (i + 1));
	if(path == NULL)
		error(22);
	path[i + 1] = '\0';
	while (i >= 0)
	{
		path[i] = env[4][i + 5];
		i--;
	}
	path2 = ft_split(path, ':');
	while (path2[i])
	{
		printf("path2 : %s\n", path2[i]);
		i++;
	}
	free(path);
	return(path2);
}
