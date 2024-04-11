/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:51:28 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/04/11 15:50:10 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_helper(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

char	*remainder(char	*my_buffer)
{
// in this function I need to get the remainder of my_buffer
// so i need to check what is after the new line character and delete everything that was before
	
	char	*new_line_positon;
	
	new_line_position = ft_strchr(my_buffer, '\n');
	
}

char	*extract_line(char *my_buffer)
{
	char	*extracted_line;
	char	*new_line_position;
	size_t	length;

	new_line_position = ft_strchr(my_buffer, '\n');
	if (new_line_position == NULL)
	{
		extracted_line = ft_strdup(my_buffer);
		if (!extracted_line)
			return (NULL);
	}
	else
	{
		length = new_line_position - my_buffer;
		extracted_line = ft_substr(my_buffer, 0, length);
		if (!extracted_line)
			return (NULL);
	}
	return (extracted_line);
}

char	*read_new_line(int fd, char *my_buffer)
{
	ssize_t	reading_bytes;
	char	*new_line;

	reading_bytes = 1;
	new_line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_line)
		return (NULL);
	new_line[BUFFER_SIZE] = '\0';
	while ((reading_bytes > 0) && (ft_strchr(my_buffer, '\n') == NULL))
	{
		reading_bytes = read(fd, new_line, BUFFER_SIZE);
		if (reading_bytes == -1)
			return (free_helper(my_buffer, new_line));
		new_line[reading_bytes] = '\0';
		my_buffer = ft_strjoin(my_buffer, new_line);
	}
	free(new_line);
	return (my_buffer);
}

char	*get_next_line(int fd)
{
	static char	*my_buffer;
	char		*line;

	my_buffer = (char *)malloc(sizeof(char));
	if (!my_buffer)
		return (NULL);
	my_buffer[0] = 0;
	my_buffer = read_new_line(fd, my_buffer);
	if (!my_buffer)
		return (NULL);
	line = extract_line(my_buffer);
	if (!line)
		return (NULL);
	my_buffer = remainder(my_buffer);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}
	line = get_next_line(fd);
	printf("%s", line);
	close(fd);
	return (0);
}
