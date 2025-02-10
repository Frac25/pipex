#include "pipex.h"

int detect_hd(char **argv)
{
	char	*limiter;
	int		fd;
	char	*line;

	if(ft_same_str(argv[1], "here_doc") == 1)
	{
		limiter = argv[2];
		fd = open("tmp_file.txt", O_CREAT | O_TRUNC |O_WRONLY, 0777);
		printf("fd = %d et limiter = %s\n", fd, limiter);

		while(1)
		{
			write(1, ">", 1);
			line = get_next_line(STDIN_FILENO);
//			write(2,line,ft_strlen(line));
			if(ft_memcmp(limiter, line, 4) == 0)
			{
				free(line);
				break; //verifier les droits
			}
			else
			{
				write(fd, line, ft_strlen(line));
				free(line);
			}
		}
//		write(2,"FIN",3);
		close(fd);
		return(1);
	}

	return(0);
}
