/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:12:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/09 10:58:00 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_wait(int i, t_struct *s)
{
	while (i-- >= 2)
		waitpid(0, NULL, 0);
	if (s->t_pid > 0)
		waitpid(s->t_pid, NULL, 0);
}

int	ft_createchildren(int argc, char **argv, char **env)
{
	t_struct	*s;
	int			fdpipe[2];
	int			i;

	s = NULL;
	ft_initstruct(argc, argv, env, &s);
	i = ft_isheredoc(argv);
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
	ft_wait(i, s);
	return (free(s), 0);
}

void	ft_firstchild(int *fdpipe, int i, t_struct *s)
{
	int	pid1;

	pid1 = fork();
	if (pid1 == 0)
	{
		if (dup2(fdpipe[1], STDOUT_FILENO) == -1)
			perror ("Pipe in Stdout");
		ft_closepipe(fdpipe);
		ft_execute(s->argv, s->env, i, s);
	}
}

void	ft_lastchild(int *fdpipe, int i, t_struct *s)
{
	int	pid2;

	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(fdpipe[0], STDIN_FILENO);
		if (ft_strcmp(s->argv[1], "here_doc") != 0)
			dup2(open(s->argv[s->argc - 1], O_WRONLY, 0644), STDOUT_FILENO);
		else
			dup2(open(s->argv[s->argc - 1], O_APPEND
					| O_WRONLY, 0644), STDOUT_FILENO);
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
