/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:51:28 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/04/18 11:33:38 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_helper(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

char	*ft_remainder(char *my_buffer)
{
	char	*new_line_position;
	char	*new_buffer;
	size_t	length;
	size_t	start;

	new_line_position = ft_strchr(my_buffer, '\n');
	if (new_line_position == NULL)
		free(my_buffer);
	length = ft_strlen(my_buffer);
	start = new_line_position - my_buffer + 1;
	new_buffer = ft_substr(my_buffer, start, length - start + 1);
	free(my_buffer);
	return (new_buffer);
}

char	*extract_line(char *my_buffer)
{
	char	*extracted_line;
	char	*new_line_position;
	size_t	length;
	int		i;

	i = 0;
	if (*my_buffer == '\0')
		return (NULL);
	if (!my_buffer[i])
		return (NULL);
	new_line_position = ft_strchr(my_buffer, '\n');
	if (new_line_position == NULL)
		extracted_line = ft_strdup(my_buffer);
	else
	{
		length = new_line_position - my_buffer + 1;
		extracted_line = ft_substr(my_buffer, 0, length);
	}
	return (extracted_line);
}

char	*read_new_line(int fd, char *my_buffer)
{
	ssize_t	reading_bytes;
	char	*new_line;
	char	*tmp;

	reading_bytes = 1;
	new_line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_line)
		return (NULL);
	new_line[BUFFER_SIZE] = '\0';
	while ((reading_bytes > 0) && (ft_strchr(my_buffer, '\n') == NULL))
	{
		reading_bytes = read(fd, new_line, BUFFER_SIZE);
		if (reading_bytes == 0 && ft_strlen(my_buffer) == 0)
			return (NULL);
		if (reading_bytes == -1)
			return (free_helper(new_line, my_buffer));
		new_line[reading_bytes] = '\0';
		tmp = ft_strjoin(my_buffer, new_line);
		if (!tmp)
			return(NULL);
		free(my_buffer);
		my_buffer = tmp;
	}
	free(new_line);
	return (my_buffer);
}

char	*get_next_line(int fd)
{
	static char	*my_buffer;
	char		*line;

	if ((fd < 0) || (BUFFER_SIZE <= 0))
		return (NULL);
	if (!my_buffer)
	{
		my_buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!my_buffer)
			return (NULL);
		my_buffer[0] = 0;
	}
	my_buffer = read_new_line(fd, my_buffer);
	if (!my_buffer)
		return (NULL);
	line = extract_line(my_buffer);
	if (!line)
		return (free(line), NULL);
	if (my_buffer[0])
		my_buffer = ft_remainder(my_buffer);
	else
		free(my_buffer);
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
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	while ((line = get_next_line(fd)) != NULL)
		printf("%s", line);
	close(fd);
	return (0);
}
