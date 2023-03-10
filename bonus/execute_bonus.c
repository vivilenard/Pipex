/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:10:37 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/06 15:28:57 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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

char	*ft_lookforaccess(char *path, char *arg, t_struct *s)
{
	char	**paths;
	char	**command;
	char	*rightpath;
	int		i;

	i = 0;
	if (access(arg, X_OK) == 0)
		return (free(s), arg);
	paths = ft_split(path, ':');
	command = ft_split(arg, ' ');
	rightpath = NULL;
	while (paths[i] && command)
	{
		paths[i] = ft_addscriptname(paths[i], command[0]);
		if (access(paths[i], X_OK) == 0)
			rightpath = ft_strdup(paths[i]);
		i++;
	}
	ft_freeacc(paths, command, rightpath, s);
	if (rightpath)
		return (rightpath);
	return (NULL);
}

char	**ft_splitonce(char *s)
{
	char	**str;
	int		i;

	str = malloc(3 * sizeof(char *));
	str[2] = NULL;
	i = 0;
	while (s[i] && ft_iswhitespace(s[i]) == 0)
		i++;
	if (!s[i])
		return (free(str), NULL);
	str[0] = malloc(i);
	ft_strlcpy(str[0], s, i + 1);
	str[1] = ft_strdup(s + i + 1);
	str[1] = ft_strtrim(str[1], "'");
	return (str);
}

int	ft_execute(char **argv, char **env, int i, t_struct *s)
{
	char	*path;
	char	**args;

	path = ft_searchbinary(env);
	path = ft_lookforaccess(path, argv[i], s);
	if (ft_strncmp(argv[i], "awk", 3) == 0
		|| ft_strncmp(argv[i], "grep", 4) == 0
		|| ft_strncmp(argv[i], "echo", 4) == 0)
		args = ft_splitonce(argv[i]);
	else
		args = ft_split(argv[i], ' ');
	if (execve(path, args, s->env) == -1)
		perror ("Execve");
	free(path);
	ft_free2d(args);
	ft_exit ();
	return (0);
}
