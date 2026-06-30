/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eroque-d <eroque-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 15:21:25 by eroque-d          #+#    #+#             */
/*   Updated: 2026/06/30 18:49:09 by eroque-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		stash = ft_strjoin_gnl(stash, buffer);
	}
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	int		count;
	int		i;
	char	*buffer;

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
	int		i;
	int		j;
	char	*buffer;

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

// char	*get_next_line(int fd)
// {
// }
