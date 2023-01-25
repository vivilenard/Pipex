/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   experiment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/25 10:22:08 by vlenard          ###   ########.fr       */
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

int	ft_execute(char **argv, char **env, int i)
{
	char *path;
	char **args;
	
	path = ft_searchbinary(env);
	path = ft_lookforaccess(path, argv[i]);
	args = ft_split(argv[i], ' ');
	if (execve(path, args, env) == -1)
		exit (0);
			ft_printf("path: %s\n", path);
	free(path);
	free(args);
	return (0);
}

void ft_closepipe(int *fdpipe)
{
	close(fdpipe[0]);
	close(fdpipe[1]);
}

int ft_makemeachild(char **argv, char **env, int i)
{
	int	pid1;
	//int	pid2;
	int	fdpipe[2];
	int	savestdout;

	i = 3;
	if (pipe(fdpipe) == -1)
		return (0);
	pid1 = fork();
		//ft_printf("hi");
	if (pid1 == 0)
	{
		if (i == 3)
		{
			dup2(fdpipe[0], STDIN_FILENO);
			ft_closepipe(fdpipe);
		}
		if (i == 2)
		{
			savestdout = dup(STDERR_FILENO);
			dup2(fdpipe[1], STDOUT_FILENO);
			ft_closepipe(fdpipe);
		}
		ft_execute(argv, env, 2);    //change 2 to i if you want recursive
		ft_closepipe(fdpipe);
	}
	ft_closepipe(fdpipe);
	// if (i == 2)
	// 	ft_makemeachild(argv, env, i++);
	wait(NULL);
	return (0);
}
	// if (i == 2)
	// {
	// 	pid2 = fork();
	// 	if (pid2 == 0)
	// 	{
	// 		dup2(fdpipe[0], STDIN_FILENO);
	// 		ft_closepipe(fdpipe);
	// 		//dup2(savestdout, STDOUT_FILENO);
	// 		ft_execute(argv, env, 3);
	// 	}
	// }


int main(int argc, char **argv, char **env)
{
	int stdin;
	int fd;
	int	i = 2;
	
	if (argc < 1)
		return (0);
	stdin = dup(STDIN_FILENO);
	fd = open("file1", O_RDONLY);
	fd = dup2(fd, STDIN_FILENO);
	ft_makemeachild(argv, env, i);
	dup2(stdin, STDIN_FILENO);
	close(fd);
	//system ("leaks pipex");
	return (0);
}
		// savestdout = dup(STDERR_FILENO);
		// dup2(fdpipe[1], STDOUT_FILENO);