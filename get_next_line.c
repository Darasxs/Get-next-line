/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:51:28 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/04/09 18:59:35 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_new_line(int fd, char *my_buffer)
{
	ssize_t	reading_bytes;
	char	*new_line;

	new_line = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!new_line)
		return (NULL);
	new_line[BUFFER_SIZE] = '\0';
	reading_bytes = 1;
	while (reading_bytes > 0 && ft_memchr(new_line, '\n',
			reading_bytes) == NULL)
	{
		reading_bytes = read(fd, new_line, BUFFER_SIZE);
		if (reading_bytes == -1)
		{
			free (my_buffer);
			free (new_line);
			return (NULL);
		}
		new_line[reading_bytes] = '\0';
		my_buffer = ft_strjoin(my_buffer, new_line);
	}
	free (new_line);
	return (my_buffer);
}

char	*get_next_line(int fd)
{
	static char	*my_buffer;
	char		*tmp;

	my_buffer = read_new_line(fd, my_buffer);
	if (!my_buffer)
		return (NULL);
}
