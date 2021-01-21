/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:14 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/20 15:27:38 by aachbaro         ###   ########.fr       */
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
	int		size;
	char	buf[2];
	char	*lines;
	char	*tmp;
	int		ret;
	int		i;

	lines = malloc(sizeof(char));
	lines[0] = 0;
	tmp = malloc(sizeof(char) * 2);
	size = 0;
	ret = read(fd, tmp, 1);
	tmp[1] = 0;
	while (buf[0] != '\n' && ret)
	{
		free(lines);
		i = 0;
		lines = malloc(sizeof(char) * (size + 2));
		while (tmp[i])
		{
			lines[i] = tmp[i];
			i++;
		}
		lines[i] = 0;
		size++;
		free(tmp);
		ret = read(fd, buf, 1);
		buf[1] = 0;
		tmp = malloc(sizeof(char) * (size + 2));
		i = 0;
		while (lines[i])
		{
			tmp[i] = lines[i];
			i++;
		}
		tmp[i++] = buf[0];
		tmp[i] = 0;
//		printf("\n\n-----\n%s\n", lines);
	}
	*line = lines;
	return (0);
}

int	main(void)
{
	int		fd;
	char	**lines;
	int		i;

	i = 0;
	lines = malloc(sizeof(char *) * 10);
	fd = open("text", O_RDONLY);
	while (i < 10)
	{
		get_next_line(fd, &lines[i]);
		printf("%s\n", lines[i]);
		i++;
	}
	return (0);
}
