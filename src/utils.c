/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:12:20 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/27 10:58:00 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_checkfiles(int argc, char **argv)
{
	open(argv[argc - 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (access(argv[1], R_OK) == -1)
	{
		ft_printf("zsh: no such file or directory: %s\n", argv[1]);
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