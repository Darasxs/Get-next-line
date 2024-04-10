/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:51:28 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/04/10 17:46:43 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_helper(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

// so far im reading one line until I enconuter a '\n'
// if my buffer size is too big, i will also read characters after a new line
// NOW I NEED: a function to extract lines that were read in the read_new_line
// then i need to take what remained in the buffer after the '\n'

char	*extract_line(int fd, char *my_buffer)
{
	char *extracted_line;
	
	while(my_buffer != NULL)
	{
		if((ft_strchr(my_buffer, '\n') != NULL))
			my_buffer = '\0';
	}
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
	line = read_new_line(fd, my_buffer); // here i will extract the line to return it with no remainder
												// here i will get only the remainder

}

//int	main(void)
//{
//	int fd;
//	char *line;
//	fd = open("test.txt", O_RDONLY);
//	if (fd == -1)
//	{
//		perror("Error opening file");
//		return (1);
//	}
//	line = get_next_line(fd);
//	printf("%s", line);
//	close(fd);
//	return (0);
//}