/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:51:28 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/04/09 13:34:39 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_new_line(int fd, char *my_buffer)
{
	ssize_t	reading_bytes;
	char	*new_line;

	reading_bytes = read(fd, my_buffer, BUFFER_SIZE);
	if (reading_bytes == -1)
		return (NULL);
	while (reading_bytes > 0 && my_buffer[reading_bytes - 1] != '\n')
	{
		if (reading_bytes == -1)
			return (NULL);
		new_line = ft_calloc(sizeof(char) * reading_bytes + 1);
		if (!new_line)
			return (NULL);
		reading_bytes = read(fd, my_buffer, BUFFER_SIZE);
		if (reading_bytes == -1)
			return (NULL);

	}
}

char	*get_next_line(int fd)
{
	static char	*my_buffer;
	char		*tmp;

	my_buffer = read_new_line(fd, my_buffer);
	if (!my_buffer)
		return (NULL);
	tmp = my_buffer;
}
