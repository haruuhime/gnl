/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmtioui <hmtioui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 01:37:39 by hmtioui           #+#    #+#             */
/*   Updated: 2025/02/11 23:25:05 by hmtioui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != (char)c)
	{
		if (*ptr == 0)
			return (NULL);
		ptr++;
	}
	return (ptr);
}

char	*reading(int fd, char *buf, char *save)
{
	ssize_t	bs;
	char	*temp;

	bs = 1;
	while (bs > 0)
	{
		bs = read(fd, buf, BUFFER_SIZE);
		if (bs == -1)
		{
			free(save);
			return (NULL);
		}
		else if (bs == 0)
			break ;
		buf[bs] = 0;
		if (!save)
			save = ft_strdup("");
		temp = save;
		save = ft_strjoin(temp, buf);
		free(temp);
		temp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (save);
}

char	*splitline(char *line)
{
	char	*newsave;
	ssize_t	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[i + 1] == 0)
		return (NULL);
	newsave = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!newsave || newsave[0] == '\0')
	{
		free(newsave);
		newsave = NULL;
	}
	line[i + 1] = 0;
	return (newsave);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*buf;
	char		*line;
	size_t		bufsize;

	bufsize = BUFFER_SIZE;
	buf = malloc((bufsize + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	if (fd < 0 || bufsize <= 0)
	{
		free(buf);
		free(save);
		save = NULL;
		buf = NULL;
		return (NULL);
	}
	line = reading(fd, buf, save);
	free(buf);
	if (!line)
		return (NULL);
	save = splitline(line);
	return (line);
}
