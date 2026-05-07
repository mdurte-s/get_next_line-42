/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdurte-s <mdurte-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:25:42 by mdurte-s          #+#    #+#             */
/*   Updated: 2026/05/07 10:00:18 by mdurte-s         ###   ########.fr       */
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
	{
		stash = clean_data(stash);
		return (NULL);
	}
	stash = new_stash(stash);
	return (str);
}

char	*read_and_stash(int fd, char *stash)
{
	int		bytes;
	char	*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (clean_data(stash));
	bytes = 1;
	while (bytes > 0 && (!stash || !ft_strchr(stash, '\n')))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			stash = clean_data(stash);
			return (clean_data(buffer));
		}
		buffer[bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	clean_data(buffer);
	if (bytes < 0 || (stash && *stash == '\0'))
	{
		stash = clean_data(stash);
		return (NULL);
	}
	return (stash);
}

char	*extract_line(char *stash)
{
	size_t	i;
	char	*new_line;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	new_line = (char *)malloc((i + (stash[i] == '\n') + 1) * sizeof(char));
	if (!new_line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		new_line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		new_line[i] = stash[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*new_stash(char *stash)
{
	char	*new;
	size_t	i;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (clean_data(stash));
	new = (char *)malloc((ft_strlen(&stash[++i]) + 1) * sizeof(char));
	if (!new)
		return (clean_data(stash));
	ft_strlcpy(new, &stash[i], ft_strlen(&stash[i]) + 1);
	stash = clean_data(stash);
	return (new);
}

char	*clean_data(char *content)
{
	if (content)
		free(content);
	return (NULL);
}
