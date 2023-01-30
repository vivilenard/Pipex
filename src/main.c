/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/30 14:25:06 by vlenard          ###   ########.fr       */
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

void	ft_firstchild(int *fdpipe, int i, t_struct *s)
{
	int	pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		if (dup2(fdpipe[1], STDOUT_FILENO) == -1)
			perror ("Pipe in Stdout");
		ft_execute(s->argv, s->env, i, s);
		ft_closepipe(fdpipe);
	}
}

void	ft_lastchild(int *fdpipe, int i, t_struct *s)
{
	int	pid2;
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fdpipe[0], STDIN_FILENO);
		dup2(open(s->argv[s->argc - 1], O_WRONLY), STDOUT_FILENO);
		ft_closepipe(fdpipe);
		ft_execute(s->argv, s->env, i, s);
	}
	ft_closepipe(fdpipe);
}

void	ft_middlechild(int *fdpipe, int i, t_struct *s)
{
	int	pid3;

	pid3 = fork();
	if (pid3 == 0)
	{
		if (dup2(fdpipe[1], STDOUT_FILENO) == -1)
			perror ("Middlepipe");
		ft_closepipe(fdpipe);
		ft_execute(s->argv, s->env, i, s);
	}
}

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
	ft_firstchild(fdpipe, i, s);
	i += 1;
	while (argc > 5 && i < argc - 2)
	{
		dup2(fdpipe[0], STDIN_FILENO);
		ft_closepipe(fdpipe);
		if (pipe(fdpipe) == -1)
		 	perror ("Middlepipe");
		ft_middlechild(fdpipe, i, s);
		i += 1;
	}
	ft_lastchild(fdpipe, i, s);
	wait(NULL);
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