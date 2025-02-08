/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarda <jsarda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 14:21:07 by jsarda            #+#    #+#             */
/*   Updated: 2023/12/01 19:49:23 by jsarda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*remaining(char *stash)
{
	int		i;
	int		j;
	char	*remaining;
	int		len;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		i++;
	len = 0;
	while (stash[i + len])
		len++;
	remaining = malloc(sizeof(char) * (len + 1));
	if (!remaining)
	{
		free(stash);
		return (NULL);
	}
	j = 0;
	while (stash[i])
		remaining[j++] = stash[i++];
	remaining[j] = '\0';
	free(stash);
	return (remaining);
}

char	*get_line(char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!*stash)
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (!line)
		return (NULL);
	j = -1;
	while (stash[++j] != '\n' && stash[j])
		line[j] = stash[j];
	if (stash[j] == '\n')
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*read_file(char *stash, int fd)
{
	char	*buffer;
	ssize_t	bytes_read;
	char	*tmp;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), NULL);
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
			return (free(stash), free(buffer), NULL);
		free(stash);
		stash = tmp;
	}
	free(buffer);
	if (bytes_read == 0 && stash && *stash == '\0')
		return (free(stash), NULL);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024] = {NULL};
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0))
		return (NULL);
	if (fd > 1024)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	stash[fd] = read_file(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	line = get_line(stash[fd]);
	stash[fd] = remaining(stash[fd]);
	if (!line)
		return (free(stash[fd]), NULL);
	return (line);
}
