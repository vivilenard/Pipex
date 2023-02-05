/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:12:20 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/05 18:11:37 by vlenard          ###   ########.fr       */
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
	if (ft_strcmp(argv[1], "here_doc") != 0)
		open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	else
		open(argv[argc - 1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (access(argv[1], R_OK) == -1)
	{
		ft_printf("zsh: no such file or directory: %s\n", argv[1]);
		ft_exit ();
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
