#include "pipex.h"


int	search_env(char *title, char **env)
{
	int	i;
	int	j;

	i = 0;
	while(env[i] != NULL)
	{
		j = 0;
		while(env[i][j] != '\0' && title[j] != '\0' && env[i][j] == title[j])
		{
			j++;
			if(title[j] == '\0')
				return(i);
		}
		i++;
	}
	return(-1);
}

char	**get_path(char **env)
{
	char	*path;
	char	**path2;
	int		line;


//	path = getenv("PATH"); // interdit
	line = search_env("PATH", env);
	path = ft_strdup2(env[line]);
//	printf("path = %s\n", path);
	path2 = ft_split(path, '=');
	free(path);
	path = ft_strdup2(path2[1]);
	free(path2);
//	printf("path = %s\n", path);
	path2 = ft_split(path, ':');
//	print_2c(path2);
	free(path);
	return(path2);
}

