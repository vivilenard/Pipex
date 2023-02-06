/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:12:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/06 22:09:06 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_createchildren(int argc, char **argv, char **env)
{
	t_struct	*s;
	int			fdpipe[2];
	int			i;

	s = NULL;
	ft_initstruct(argc, argv, env, &s);
	i = 2;
	if (pipe(fdpipe) == -1)
		perror ("Pipe");
	ft_firstchild(fdpipe, i, s);
	i += 1;
	ft_lastchild(fdpipe, i, s);
	waitpid(0, NULL, 0);
	waitpid(0, NULL, 0);
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
		dup2(open(s->argv[s->argc - 1], O_WRONLY, 0644), STDOUT_FILENO);
		ft_closepipe(fdpipe);
		ft_execute(s->argv, s->env, i, s);
	}
	ft_closepipe(fdpipe);
}
