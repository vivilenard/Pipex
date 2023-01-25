/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:10:37 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/25 12:22:00 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

char	*ft_addscriptname(char *path, char *command)
{
	char	*newpath;

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
	if (!command || !paths)
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
	char	*path;
	char	**args;

	path = ft_searchbinary(env);
	path = ft_lookforaccess(path, argv[i]);
	args = ft_split(argv[i], ' ');
	if (execve(path, args, env) == -1)
		exit (0);
	free(path);
	free(args);
	return (0);
}
