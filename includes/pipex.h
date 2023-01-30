/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:11:55 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/30 16:26:40 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"

typedef struct s_struct
{
	char	**argv;
	int		argc;
	char	**env;
	int		heredoc;
}				t_struct;

char	*ft_searchbinary(char **env);
char	*ft_addscriptname(char *path, char *command);
char	*ft_lookforaccess(char *path, char *arg);
int		ft_execute(char **argv, char **env, int i, t_struct *s);
void	ft_checkfiles(int argc, char **argv);
void	ft_closepipe(int *fdpipe);
void	ft_emptystr(int argc, char **argv);
void	ft_initstruct(int argc, char **argv, char **env, t_struct **s);
void	ft_firstchild(int *fdpipe, int i, t_struct *s);
void	ft_lastchild(int *fdpipe, int i, t_struct *s);
void	ft_middlechild(int *fdpipe, int i, t_struct *s);
int		ft_makemeachild(int argc, char **argv, char **env);
int		ft_isheredoc(char **argv);
void	ft_heredoc(char **argv);

#endif