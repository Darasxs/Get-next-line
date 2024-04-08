/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:51:28 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/04/08 12:28:55 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*my_buffer;
	ssize_t		reading_bytes;
	char		*new_line;

	my_buffer = ft_calloc(BUFFER_SIZE + 1);
	if (!my_buffer)
		return (NULL);
	reading_bytes = read(fd, my_buffer, BUFFER_SIZE);
	if (reading_bytes == -1)
		return (-1);
	new_line = ft_calloc(sizeof(char) * reading_bytes + 1);
	if (!new_line)
		return (NULL);
}

// static variable
// a variable that its lifetime is the entire run of the program
// automatic variables on the other hand are stack allocated and deallocated on the call stack

// static memory allocation is the allocation at compile time,
// before the program is executed
// dynamic allocaiton is when the memory is allocated at run time

// read from the fd into a buffer (in a loop)
// it will read in a loop until a newline  is encountered or it's EOF
// after a newline is encountered, i will have to split the buffer at this point
// store the previous line should be returned,
// the part after the newline should be store in the static variable
// if we reach EOF, we should rerturn everything from the static variable
// if static variable is empty, return NULL
// static variable will hold data that is left over from one read operation to the next
// also need to handle multiple file descriptors

// file descriptor is an integer that uniquely identifies an open file of the process