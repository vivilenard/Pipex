/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/23 20:57:36 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_searchbinary(char **env)
{
	int	i;

	i = 0;
	while (*env[i])
	{
		if (ft_haystack(env[i], "PATH") != NULL)
			return (env[i]);
		i++;
	}
	return (NULL);
}

void	ft_lookforaccess(char **path)
{
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(*path, ':');
	if (!paths)
		exit (0);
	//free (path);
	ft_printf("\nHere are the paths:\n");
	while (path[i])
	{
		ft_putstr_fd(paths[i], 1);
		write (1, "\n", 1);
		if (access(paths[i], X_OK) == 0)
		{
			ft_printf("success!!!!!! for %i\n", i);      //hier bin ich
		}
		i++;
	}
}

int ft_makemeachild(int *fdpipe, char **argv, char **env)
{
	int	pid1;
	char *path;

	ft_printf("av: %s\n", argv[2]);
	pid1 = fork();
	if (pid1 == 0)
	{
		path = ft_searchbinary(env);
		ft_printf("Path is: %s\n", path);
		if (path == NULL)
			exit (0);
		ft_lookforaccess(&path);
							ft_printf("PID1 = %d hi\n", pid1);
		ft_printf("pid1 %d\n fdpipe %d\n", pid1, fdpipe[0]);
	}
	wait(NULL);
	return (0);
}


int main(int argc, char **argv, char **env)
{
	int stdin;
	int fd;
	int	fdpipe[1];
	int n;
	
	if (argc < 1)
		return (0);
	//replace stdin with file1
	stdin = dup(STDIN_FILENO);
	fd = open("file1", O_RDONLY);
	fd = dup2(fd, STDIN_FILENO);
	ft_printf("stdin: %d, file1: %d\n", stdin, fd);
	
	//search for 

	//create pipe
	if (pipe(fdpipe) == -1)
		return (0);
		
	//fork
	n = 2;
	ft_makemeachild(fdpipe, argv, env);

	//go back to normal
	dup2(stdin, STDIN_FILENO);
	close(fd);
	return (0);
}
		//look for path of argv[n]
		// pid2 = fork();
		// if (pid2 == 0)
		// {
		// 			ft_printf("PID2 = %d hi\n", pid2);
		// 			ft_printf("pipe: %d\n", fdpipe[0]);
		// }