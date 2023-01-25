/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/25 12:25:57 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_makemeachild(int argc, char **argv, char **env)
{
	int	pid1;
	int	pid2;
	int	fdpipe[2];

	if (pipe(fdpipe) == -1)
		return (0);
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fdpipe[1], STDOUT_FILENO);
		ft_execute(argv, env, 2);
		ft_closepipe(fdpipe);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fdpipe[0], STDIN_FILENO);
		dup2(open(argv[argc - 1], O_WRONLY), STDOUT_FILENO);
		ft_closepipe(fdpipe);
		ft_execute(argv, env, 3);
	}
	wait(NULL);
	ft_closepipe(fdpipe);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int	stdin;
	int	fd;

	if (argc < 5)
		return (0);
	ft_checkfiles(argc, argv);
	stdin = dup(STDIN_FILENO);
	fd = open(argv[1], O_RDONLY);
	fd = dup2(fd, STDIN_FILENO);
	ft_makemeachild(argc, argv, env);
	close(fd);
	return (0);
}
	//system ("leaks pipex");