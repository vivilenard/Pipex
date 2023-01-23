/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:35:47 by vlenard           #+#    #+#             */
/*   Updated: 2022/12/02 13:12:23 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_readtostat(int fd, char *stat)
{
	int		flag;
	char	*buf;

	flag = 9;
	while (flag != 0 && ft_strchr(stat, '\n') == 0)
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		flag = read(fd, buf, BUFFER_SIZE);
		if (flag == -1)
			return (free(buf), free(stat), NULL);
		if (flag == 0)
			return (free(buf), stat);
		buf[flag] = '\0';
		stat = ft_strjoin(stat, buf);
	}
	return (stat);
}

char	*ft_addanend(char *stat, char **line, int i)
{
	char	*buf;

	if (stat[i] == '\0')
	{
		*(*line + i) = '\0';
		return (free (stat), NULL);
	}
	if (stat[i] == '\n')
	{
		*(*line + i) = '\n';
		*(*line + i + 1) = '\0';
		if (stat[i + 1] == '\0')
			return (free (stat), NULL);
	}
	buf = ft_strdup(stat + i + 1);
	return (free (stat), buf);
}

char	*ft_stattoline(char *stat, char **line)
{
	int	i;

	i = 0;
	while (stat[i] != '\n' && stat[i] != '\0')
		i++;
	if (stat[i] == '\n')
		*line = malloc(i + 2);
	else if (stat[i] == '\0')
		*line = malloc(i + 1);
	if (!*line)
		return (NULL);
	i = 0;
	while (stat[i] != '\n' && stat[i] != '\0')
	{
		*(*line + i) = stat[i];
		i++;
	}
	return (ft_addanend(stat, line, i));
}

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*line;

	line = NULL;
	stat = ft_readtostat(fd, stat);
	if (stat == NULL)
		return (NULL);
	stat = ft_stattoline(stat, &line);
	return (line);
}
