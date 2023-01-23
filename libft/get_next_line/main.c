#include "get_next_line.c"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


int	main()
{
	int	fd;
	char *line;
	int i = 0;

	fd = open("big_line_no_nl", O_RDONLY);
	line = get_next_line(fd);
	while(line)
	{
		printf("LINE: %s", line);
		line = get_next_line(fd);
		i++;
	}
	printf("LINE: %s\n", line);
	/*
	line = get_next_line(fd);
	printf("LINE: %s\n", line);
	line = get_next_line(fd);
	printf("LINE: %s\n", line);
	*/
	close(fd);
	//system("leaks a.out");
	return (0);
}