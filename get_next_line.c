/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aachbaro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:39:14 by aachbaro          #+#    #+#             */
/*   Updated: 2021/01/25 14:44:31 by aachbaro         ###   ########.fr       */
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

	ret = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	str = malloc(sizeof(char) * 1);
	str[0] = 0;
	tmp = ft_strdup("");
	while (ft_strchr(buf, '\n') == NULL && ret)
	{
		free(str);
		ret = read(fd, buf, BUFFER_SIZE);
		buf[BUFFER_SIZE] = 0;
		if (ft_strchr(tmp, '\n') != NULL)
		{
			str = ft_substr(tmp, 0, ft_strchr(tmp, '\n') - tmp);
			tmp = ft_substr(tmp, ft_strchr(tmp, '\n') - tmp, ft_strlen(tmp));
		}
		else if (ft_strchr(buf, '\n') != NULL)
		{
			str = ft_strjoin(tmp, ft_substr(buf, 0, ft_strchr(buf, '\n') - buf));
			tmp = ft_substr(buf, ft_strchr(buf, 'n') - buf, ft_strlen(buf));
		}
		else
		{
			str = ft_strjoin(tmp, buf);
			tmp = ft_strdup(str);
		}

	}
	*line = ft_substr(str, 0, ft_strlen(str));
	return (ret);
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
		printf("%d - ",get_next_line(fd, &line[i]));
		printf("%s\n", line[i]);
		i++;
	}
	return (0);
}
