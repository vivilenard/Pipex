/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karllenard <karllenard@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:12:20 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/07 08:43:46 by karllenard       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_initstruct(int argc, char **argv, char **env, t_struct **s)
{
	*s = malloc(sizeof(t_struct *));
	(*s)->argc = argc;
	(*s)->argv = argv;
	(*s)->env = env;
}

void	ft_checkfiles(int argc, char **argv)
{
	int	fd;

	fd = open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (access(argv[argc - 1], R_OK) == -1)
	{
		perror(argv[argc - 1]);
		ft_exit ();
	}
	if (access(argv[1], F_OK) == -1)
	{
		perror(argv[1]);
		ft_exit ();
	}
	if (access(argv[1], R_OK) == -1)
		perror(argv[1]);
	close (fd);
}

void	ft_emptystr(int argc, char **argv)
{
	int	i;

	i = 0;
	while (i < argc)
	{
		if (!argv[i][0])
		{
			ft_printf("You entered an empty string.\n");
			ft_printf("Please fill it with a shell command.\n");
			ft_exit ();
		}
		i++;
	}
}

void	ft_closepipe(int *fdpipe)
{
	if (close(fdpipe[0]) == -1)
		perror ("Closing pipe");
	if (close(fdpipe[1]) == -1)
		perror ("Closing pipe");
}

void	ft_freeacc(char **paths, char **command, char *rightpath, t_struct *s)
{
	if (!rightpath)
	{
		write(2, "zsh: command not found: ", 24);
		ft_putstr_fd(command[0], 2);
		write(2, "\n", 1);
	}
	if (paths)
		ft_free2d(paths);
	if (command)
		ft_free2d(command);
	if (rightpath == NULL)
	{
		free (s);
		ft_exit ();
	}
}
