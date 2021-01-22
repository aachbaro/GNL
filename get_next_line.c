/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:14 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/22 15:16:59 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int	get_next_line(int fd, char **line)
{
	static char *tmp = NULL;
	char		*buf;
	char		*str;
	int			ret;
	int			size;

	ret = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	str = malloc(sizeof(char));
	if (!buf || !str)
		return (NULL);
	size = ft_strlen(tmp);
	while(ft_strchr(buf, '\n') == NULL && ret)
	{
		free(str);
		ret = read(fd, buf, BUFFER_SIZE);
		buf[BUFFER_SIZE + 1] = 0;
		str = malloc(sizeof(char) * (size + ft_strlen(buf);
	}
	return (0);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text", O_RDONLY);
	get_next_line(fd, &line);
	printf("\n %s", line);
	return (0);
}
