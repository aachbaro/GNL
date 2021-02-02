/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:14 by aachbaro          #+#    #+#             */
/*   Updated: 2021/02/02 13:34:40 by aachbaro         ###   ########.fr       */
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
	char		*str;
	int			ret;
	int			i;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	i = 0;
	while (i < BUFFER_SIZE + 1)
		buf[i++] = 0;
	str = NULL;
	ret = 1;
	if (!tmp)
		tmp = ft_strdup("");
	while (!ft_strchr(buf, '\n') && !ft_strchr(tmp, '\n') && ret)
	{
//		free(str);
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
//			free(tmp);
			return (-1);
		}
		buf[ret] = 0;
		if (!(str = ft_strjoin(tmp, buf)))
		{
//			free(tmp);
			return (-1);
		}
		if (!(tmp = ft_strdup(str)))
		{
//			free(str);
			return (-1);
		}
	}
	if (ft_strchr(tmp, '\n') != NULL && str)
	{
//		free(str);
		if (!(str = ft_substr(tmp, 0, ft_strchr(tmp, '\n') - tmp)))
		{
//			free(tmp);
			return (-1);
		}
		if (!(tmp = ft_substr(tmp, ft_strchr(tmp, '\n') - tmp + 1, ft_strlen(tmp))))
		{
//			free(str);
			return (-1);
		}
	}
	else if (ft_strchr(buf, '\n') != NULL)
	{
//		free(str);
		if (!(str = ft_strjoin(tmp, ft_substr(buf, 0, ft_strchr(buf, '\n') - buf))))
		{
//			free(tmp);
			return (-1);
		}
//		free(tmp);
		if (!(tmp = ft_substr(buf, ft_strchr(buf, '\n') - buf + 1, ft_strlen(buf))))
		{
//			free(str);
			return (-1);
		}
	}
	else
		free(tmp);
	*line = str;
	if (ret == 0 && *str == 0)
		return (0);
	return (1);
}
 
/*int	main(void)
{
	int		fd;
	char	**line;
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	fd = open("text", O_RDONLY);
	line = malloc(sizeof(char *) * 10);
	while (ret)
	{
		printf("\n%d - ", ret = get_next_line(fd, &line[i]));
		printf("%s\n", line[i]);
		i++;
	}
	return (0);
}*/

#include <fcntl.h>

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




