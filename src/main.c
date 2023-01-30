/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/30 16:32:31 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **env)
{
	int	stdin;
	int	fd;

	if (argc < 5)
		return (0);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		ft_heredoc(argv);
	ft_checkfiles(argc, argv);
	ft_emptystr(argc, argv);
	stdin = dup(STDIN_FILENO);
	fd = open(argv[1], O_RDONLY);
	fd = dup2(fd, STDIN_FILENO);
	ft_makemeachild(argc, argv, env);
	close(fd);
	system ("leaks pipex");
	return (0);
}
