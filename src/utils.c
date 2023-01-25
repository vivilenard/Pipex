/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 12:12:20 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/25 12:19:21 by vlenard          ###   ########.fr       */
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

void	ft_closepipe(int *fdpipe)
{
	close(fdpipe[0]);
	close(fdpipe[1]);
}
