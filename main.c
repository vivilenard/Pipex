/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/24 20:21:41 by vlenard          ###   ########.fr       */
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

char *ft_addscriptname(char *path, char *command)
{
	char *newpath;


	newpath = ft_strjoin(path, "/");
	newpath = ft_strjoin(newpath, command);
	return (newpath);
}


char	*ft_lookforaccess(char *path, char *arg)
{
	char	**paths;
	char	**command;
	char	*rightpath;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	command = ft_split(arg, ' ');
	rightpath = NULL;
	if (!command)
		exit (0);
	if (!paths)
		exit (0);
	while (paths[i])
	{
		paths[i] = ft_addscriptname(paths[i], command[0]);
		if (access(paths[i], X_OK) == 0)
			rightpath = ft_strdup(paths[i]);
		i++;
	}
	ft_free2d(paths);
	ft_free2d(command);
	if (rightpath)
		return (rightpath);
	return (NULL);
}

int ft_makemeachild(char **argv, char **env)
{
	int	pid1;
	char *path;
	char **args;

	pid1 = fork();
	if (pid1 == 0)
	{
		path = ft_searchbinary(env);
		path = ft_lookforaccess(path, argv[2]);
		args = ft_split(argv[2], ' ');
		if (execve(path, args, env) == -1)
			exit (0);
				ft_printf("path: %s\n", path);
		free(path);
		free(args);
	}
	wait(NULL);
	return (0);
}


int main(int argc, char **argv, char **env)
{
	int stdin;
	int fd;
	int	fdpipe[1];
	
	if (argc < 1)
		return (0);
	stdin = dup(STDIN_FILENO);
	fd = open("file1", O_RDONLY);
	fd = dup2(fd, STDIN_FILENO);
	if (pipe(fdpipe) == -1)
		return (0);
	ft_makemeachild(argv, env);

	dup2(stdin, STDIN_FILENO);
	close(fd);
	//system ("leaks pipex");
	return (0);
}
