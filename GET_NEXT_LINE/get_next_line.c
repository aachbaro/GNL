/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:14 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/29 15:28:54 by aachbaro         ###   ########.fr       */
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
	static char *tmp;
	char		buf[BUFFER_SIZE + 1];
	int			ret;

	if (!line || BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	if (!tmp)
		tmp = ft_strdup("");
	*line = NULL;
	while (!ft_strchr(tmp, '\n') && (ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[ret] = 0;
	//	free(line);
		if (!(*line = ft_strdup(tmp)))
		{
			free(tmp);
			return (-1);
		}
		if (!(tmp = ft_strjoin(*line, buf)))
			return (-1);
	}
	if (ft_strchr(tmp, '\n'))
	{
		free(*line);
		*line = ft_substr(tmp, 0, ft_strchr(tmp, '\n') - tmp);
		if (!(tmp = ft_substr(tmp, ft_strchr(tmp, '\n') - tmp + 1, ft_strlen(tmp))))
			return (-1);
	}
	else
	{
		*line = tmp;
		free(tmp);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	char *line;
	int fd;
	int ret;
	int countline;

	countline = 1;
	if (ac == 1)
		fd = 0;
	if (ac >= 2)
		fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line))==1)
    {
		printf("line %d = %s - [%d]\n", countline, line, ret);
    	free(line);
		countline++;
    }
	printf("line %d = %s - [%d]\n", countline, line, ret);
	free(line);

	printf("\nTest de LEAKS\n");
	system("leaks a.out | grep leaked\n");
	return 0;
}
