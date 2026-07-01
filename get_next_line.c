/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eroque-d <eroque-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 15:21:25 by eroque-d          #+#    #+#             */
/*   Updated: 2026/07/01 14:21:08 by eroque-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_buffer(int fd, char *stash, char *buffer, size_t size)
{
	size_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, size);
		if (bytes_read == -1)
			return (free(stash), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = ft_strjoin_gnl(stash, buffer);
		if (!stash)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	size_t	size;

	if (stash && ft_strchr(stash, '\n'))
		return (stash);
	size = BUFFER_SIZE;
	buffer = malloc(size + 1);
	if (!buffer)
	{
		free(stash);
		return (NULL);
	}
	stash = append_buffer(fd, stash, buffer, size);
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t		count;
	size_t		i;
	char		*buffer;

	if (!stash || !*stash)
		return (NULL);
	count = 0;
	while (stash[count] && stash[count] != '\n')
		count++;
	if (stash[count] == '\n')
		count++;
	buffer = malloc(count + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (i < count)
	{
		buffer[i] = stash[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}

static char	*clean_stash(char *stash)
{
	size_t		i;
	size_t		j;
	char		*buffer;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || !stash[i + 1])
	{
		free(stash);
		return (NULL);
	}
	i++;
	buffer = malloc(ft_strlen(&stash[i]) + 1);
	if (!buffer)
		return (NULL);
	j = 0;
	while (stash[i])
		buffer[j++] = stash[i++];
	buffer[j] = '\0';
	free(stash);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	stash = read_and_stash(fd, stash);
	if (!stash || *stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
