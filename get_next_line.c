/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:14 by aachbaro          #+#    #+#             */
/*   Updated: 2021/02/02 15:46:00 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

char	*get_line(char *tmp)
{
	size_t	i;
	char	*str;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		str[i] = tmp[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*get_tmp(char *tmp)
{
	if (ft_strchr(tmp, '\n'))
	{
		tmp = ft_strchr(tmp, '\n') + 1;
		if (!tmp)
			return (NULL);
	}
	else
		tmp = ft_strdup("");
	return (tmp);
}

int		get_next_line(int fd, char **line)
{
	static char *tmp;
	char		buf[BUFFER_SIZE + 1];
	int			ret;

	if (!line || BUFFER_SIZE <= 0 || fd < 0)
		return (-1);
	if (!tmp)
		tmp = ft_strdup("");
	ret = 1;
	while (!ft_strchr(tmp, '\n') && ret)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		buf[ret] = 0;
		tmp = ft_strjoin(tmp, buf);
	}
	*line = get_line(tmp);
	if (!line)
	{
		free(tmp);
		return (-1);
	}
	tmp = get_tmp(tmp);
	if (!tmp)
		return (-1);
	if (ret == 0 && **line == 0 && *tmp == 0)
	{
		free(tmp);
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	char	*line;
	int		fd;
	int		ret;
	int		countline;

	countline = 1;
	if (ac == 1)
		fd = 0;
	if (ac >= 2)
		fd = open(av[1], O_RDONLY);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		printf("line %d = %s - [%d]\n", countline, line, ret);
		free(line);
		countline++;
	}
	printf("line %d = %s - [%d]\n", countline, line, ret);
	free(line);
	printf("\nTest de LEAKS\n");
	system("leaks a.out | grep leaked\n");
	return (0);
}
