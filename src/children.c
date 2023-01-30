/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:12:59 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/30 16:36:45 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_heredoc(char **argv)
{
	int		fd;
	char	*line;

	fd = open("here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	while (1)
	{
		write(0, ">", 1);
		line = get_next_line(0);
		if (!line)
			perror("gets no line");
		if (ft_strncmp(argv[2], line, ft_strlen(argv[2])) == 0)
		{
			free(line);
			return ;
		}
		if (write(fd, line, ft_strlen(line)) == -1)
			perror("write to here_doc.txt");
		free (line);
	}
}

int	ft_makemeachild(int argc, char **argv, char **env)
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
