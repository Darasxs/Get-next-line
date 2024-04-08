/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:51:28 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/04/08 16:52:43 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*my_buffer;
	ssize_t		reading_bytes;
	char		*new_line;

	if (!my_buffer)
	{
		my_buffer = ft_calloc(BUFFER_SIZE + 1);
		if (!my_buffer)
			return (NULL);
	}
	reading_bytes = read(fd, my_buffer, BUFFER_SIZE);
	while (reading_bytes > 0 && my_buffer[reading_bytes - 1] != '\n')
	{
		if (reading_bytes == -1)
			return (-1);
		new_line = ft_calloc(sizeof(char) * reading_bytes + 1);
		if (!new_line)
			return (NULL);
		reading_bytes = read(fd, my_buffer, BUFFER_SIZE);
	}
	return (new_line);
}
