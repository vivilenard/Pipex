/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/27 15:30:49 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void ft_initstruct(int argc, char **argv, char **env, t_struct **s)
{
	*s = malloc(sizeof(t_struct *));
	(*s)->argc = argc;
	(*s)->argv = argv;
	(*s)->env = env;
}

void	ft_child_one(int *fdpipe, int i, char **argv, char **env)
{
	int	pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		if (dup2(fdpipe[1], STDOUT_FILENO) == -1)
			perror ("Pipe in Stdout");
		ft_execute(argv, env, i);
		ft_closepipe(fdpipe);
	}
}

void	ft_child_two(int *fdpipe, int i, char **argv, char **env)
{
	int	pid2;
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fdpipe[0], STDIN_FILENO);
		//argc = 1; //dont need
		//dup2(open(s->argv[s->argc - 1], O_WRONLY), STDOUT_FILENO);
		ft_closepipe(fdpipe);
		ft_execute(argv, env, i);
	}
}

// void	ft_child_middle(int *fdpipe, char **argv, char **env)
// {
// 	int	pid2;
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		dup2(fdpipe[0], STDIN_FILENO);
// 		if (pipe(fdpipe) == -1)
// 			perror ("Middlepipe");
// 		dup2(fdpipe[1], STDOUT_FILENO) == -1;
// 		ft_closepipe(fdpipe);
// 		ft_execute(argv, env, 3);
// 	}
// }

int	ft_makemeachild(int argc, char **argv, char **env)
{
	t_struct *s;
	int	fdpipe[2];
	int	i;

	s = NULL;
	ft_initstruct(argc, argv, env, &s);
	i = 2;
	if (pipe(fdpipe) == -1)
		perror ("Pipe");
	ft_child_one(fdpipe, i, argv, env);
	// while (argv < 5 && i < argv - 5)
	// {
	// 	ft_child_middle(fdpipe, argv, env);
	// }
	ft_child_two(fdpipe, i + 1, argv, env);
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
	ft_emptystr(argc, argv);
	stdin = dup(STDIN_FILENO);
	fd = open(argv[1], O_RDONLY);
	fd = dup2(fd, STDIN_FILENO);
	ft_makemeachild(argc, argv, env);
	close(fd);
	//system ("leaks pipex");
	return (0);
}