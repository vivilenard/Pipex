/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:12:20 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/30 16:32:02 by vlenard          ###   ########.fr       */
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

int	ft_isheredoc(char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		return (3);
	return (2);
}

void	ft_checkfiles(int argc, char **argv)
{
	open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (access(argv[1], R_OK) == -1)
	{
		ft_printf("zsh: no such file or directory: %s\n", argv[1]);
		system ("leaks pipex");
		exit (0);
	}
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
			system ("leaks pipex");
			exit (0);
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
