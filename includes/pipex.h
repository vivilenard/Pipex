/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:11:55 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/25 22:12:12 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include "../libft/libft.h"

char	*ft_searchbinary(char **env);
char	*ft_addscriptname(char *path, char *command);
char	*ft_lookforaccess(char *path, char *arg);
int		ft_execute(char **argv, char **env, int i);
void	ft_checkfiles(int argc, char **argv);
void	ft_closepipe(int *fdpipe);
void	ft_emptystr(int argc, char **argv);

#endif