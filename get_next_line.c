/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdurte-s <mdurte-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:16:13 by mdurte-s          #+#    #+#             */
/*   Updated: 2026/05/04 00:28:15 by mdurte-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*str;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	str = extract_line(stash);
	if (!str)
		return (NULL);
	stash = new_stash(stash);
	if (!stash)
		clean_data(stash);
	return (str);
}

char	*read_and_stash(int fd, char *stash)
{
	int		bytes;
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (bytes > 0 && (!stash || !ft_strchr(stash, '\n')))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			clean_data(buffer);
			return (clean_data(stash));
		}
		buffer[bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	clean_data(buffer);
	if (bytes < 0)
		return (clean_data(stash));
	return (stash);
}

char	*extract_line(char *stash)
{
	size_t	i;
	char	*new_line;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	new_line = (char *)malloc((i + 2) * sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		new_line[i] = stash[i];
		i++;
	}
	new_line[i] = stash[i];
	new_line[i + 1] = '\0';
	return (new_line);
}

char	*new_stash(char *stash)
{
	char	*new;
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (clean_data(stash));
	new = (char *)malloc((ft_strlen(&stash[++i]) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, &stash[i], ft_strlen(&stash[i]) + 1);
	clean_data(stash);
	return (new);
}

char	*clean_data(char *content)
{
	free(content);
	return (NULL);
}
