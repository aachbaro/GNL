/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:14 by aachbaro          #+#    #+#             */
/*   Updated: 2021/02/03 11:59:40 by aachbaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

char	*loop_buf(int fd, int *ret, char *tmp)
{
	char	*str;
	char	buf[BUFFER_SIZE + 1];

	while (!ft_strchr(tmp, '\n') && *ret)
	{
		*ret = read(fd, buf, BUFFER_SIZE);
		buf[*ret] = 0;
		str = malloc(sizeof(char *) ft_strlen(tmp));
		i = 0;
		j = 0;
		while (tmp[i])
			str[j++] = tmp[i++];
		str[j] = 0;
		free(tmp);
		ft_strjoin(str, buf);
		i = 0;
		j = 0;
		while (str[i])
			tmp[j++] = str[i++];
		tmp[j] = 0;
		free(str);
	}
	return (tmp);
}	

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
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (tmp[i] == 0)
	{
		free(tmp);
		return (ft_strdup(""));
	}
	str = malloc(sizeof(char) * (ft_strlen(tmp) - i - 1));
	if (!str)
		return (NULL);
	j = 0;
	i++;
	while (tmp[i])
		str[j++] = tmp[i++];
	free(tmp);
	str[j] = 0;
	return (str);
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
