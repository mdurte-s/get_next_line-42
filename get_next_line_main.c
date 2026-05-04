/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdurte-s <mdurte-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:31:47 by mdurte-s          #+#    #+#             */
/*   Updated: 2026/05/04 21:14:38 by mdurte-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

int	main(void)
{
	int		file_descriptor;
	char	*line;

	file_descriptor = open("file.txt", O_RDONLY);
	if (file_descriptor < 0)
		return (1);
	while ((line = get_next_line(file_descriptor)))
	{
		printf("%s", line);
		free(line);
	}
	close(file_descriptor);
	return (0);
}
