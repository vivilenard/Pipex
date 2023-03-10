/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:13:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/09 12:30:36 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_exit(void)
{
	unlink("here_doc");
	unlink ("empty");
	exit (0);
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
		ft_printf("Please enter 'infile'(/ here_doc + 'delimiter)");
		ft_printf(" at least two commands as strings and 'outfile'\n");
		return (0);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
		ft_heredoc(argv);
	ft_checkfiles(argc, argv);
	ft_emptystr(argc, argv);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		fd = open("empty", O_CREAT | O_RDONLY);
	fd = dup2(fd, STDIN_FILENO);
	ft_createchildren(argc, argv, env);
	close (fd);
	ft_exit();
	return (0);
}
