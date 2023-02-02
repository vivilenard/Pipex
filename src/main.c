/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/02 16:11:27 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exit ()
{
	unlink("here_doc");
	system ("leaks pipex");
	exit (0);
}

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
		{
			perror("gets no line");
			ft_exit ();
		}
		if (ft_strncmp(argv[2], line, ft_strlen(argv[2])) == 0
			&& ft_strlen(line) == ft_strlen(argv[2]) + 1)
		{
			free(line);
			return ;
		}
		if (write(fd, line, ft_strlen(line)) == -1)
			perror("write to here_doc.txt");
		free (line);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	fd;

	if (argc < 5)
	{
		ft_printf("Please enter 'infile', two commands");
		ft_printf(" as strings and 'outfile'\n");
		return (0);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
		ft_heredoc(argv);
	ft_checkfiles(argc, argv);
	ft_emptystr(argc, argv);
	fd = open(argv[1], O_RDONLY);
	fd = dup2(fd, STDIN_FILENO);
	ft_createchildren(argc, argv, env);
	ft_exit();
	return (0);
}
