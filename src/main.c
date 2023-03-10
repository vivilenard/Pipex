/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/09 12:30:22 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exit(void)
{
	unlink("empty");
	exit (0);
}

int	main(int argc, char **argv, char **env)
{
	int	fd;

	if (!env)
		perror("env");
	if (argc != 5)
	{
		ft_printf("Please enter 'infile', two commands");
		ft_printf(" as strings and 'outfile'\n");
		return (0);
	}
	ft_checkfiles(argc, argv);
	ft_emptystr(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		fd = open("empty", O_CREAT | O_RDONLY);
	fd = dup2(fd, STDIN_FILENO);
	ft_createchildren(argc, argv, env);
	ft_exit();
	return (0);
}
