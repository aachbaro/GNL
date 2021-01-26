/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:14 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/26 15:38:48 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int	endline_in_tmp(char **tmp, char **str)
{
	*str = ft_substr(*tmp, 0, ft_strchr(*tmp, '\n') - *tmp);
	*tmp = ft_substr(*tmp, ft_strchr(*tmp, '\n') - *tmp + 1, ft_strlen(*tmp));
	if (*str == NULL || *tmp == NULL)
		return (-1);
	return (0);
}

int	endline_in_buf(char **tmp, char **str, char **buf)
{
	*str = ft_strjoin(*tmp, ft_substr(*buf, 0, ft_strchr(*buf, '\n') - *buf));
	*tmp = ft_substr(*buf, ft_strchr(*buf, '\n') - *buf + 1, ft_strlen(*buf));
	if (*str == NULL || *tmp == NULL)
		return (-1);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char *tmp;
	char		*buf;
	char		*str;
	int			ret;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	str = malloc(sizeof(char) * 1);
	ret = 1;
	if (!tmp)
		tmp = ft_strdup("");
	while (!ft_strchr(buf, '\n') && !ft_strchr(tmp, '\n') && ret)
	{
		free(str);
		ret = read(fd, buf, BUFFER_SIZE);
		buf[BUFFER_SIZE] = 0;
		str = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = ft_strdup(str);
	}
	if (ft_strchr(tmp, '\n') != NULL)
		endline_in_tmp(&tmp, &str);
	else if (ft_strchr(buf, '\n') != NULL)
		endline_in_buf(&tmp, &str, &buf);
	*line = ft_strdup(str);
	return (0);
}

int	main(void)
{
	int		fd;
	char	**line;
	int		i;

	i = 0;
	fd = open("text", O_RDONLY);
	line = malloc(sizeof(char *) * 10);
	while (i < 4)
	{
		printf("\n%d - ", get_next_line(fd, &line[i]));
		printf("%s\n", line[i]);
		i++;
	}
	return (0);
}
