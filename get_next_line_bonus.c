/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:44:17 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/04/19 14:03:44 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_helper(char **s1, char **s2, char c)
{
	if (c)
		free(*s1);
	free(*s2);
	*s2 = NULL;
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
	{
		free(my_buffer);
		return (NULL);
	}
	length = ft_strlen(my_buffer) + 1;
	start = new_line_position - my_buffer + 1;
	new_buffer = ft_substr(my_buffer, start, length - start);
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
			return (free(new_line), my_buffer);
		if (reading_bytes == -1)
			return (free_helper(&new_line, &my_buffer, 1));
		new_line[reading_bytes] = '\0';
		tmp = ft_strjoin(my_buffer, new_line);
		if (!tmp)
			return (NULL);
		free(my_buffer);
		my_buffer = tmp;
	}
	free(new_line);
	return (my_buffer);
}

char	*get_next_line(int fd)
{
	static char	*my_buffer[FOPEN_MAX];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	if (!my_buffer[fd])
	{
		my_buffer[fd] = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!my_buffer[fd])
			return (NULL);
		my_buffer[fd][0] = 0;
	}
	my_buffer[fd] = read_new_line(fd, my_buffer[fd]);
	if (!my_buffer[fd])
		return (free_helper(NULL, &my_buffer[fd], 0));
	line = extract_line(my_buffer[fd]);
	if (!line)
		return (free_helper(NULL, &my_buffer[fd], 0));
	if (my_buffer[fd][0])
		my_buffer[fd] = ft_remainder(my_buffer[fd]);
	else
		free_helper(NULL, &my_buffer[fd], 0);
	return (line);
}

// int	main(void)
//{
//	int		fd1;
//	int		fd2;
//	int		fd3;

//	char	*line;

//	fd1 = open("test.txt", O_RDONLY);
//	fd2 = open("test2.txt", O_RDONLY);
//	fd3 = open("test3.txt", O_RDONLY);

//	if (fd1 == -1 || fd2 == -1 || fd3 == -1)
//	{
//		perror("Error opening file");
//		return (1);
//	}
//	while ((line = get_next_line(fd1)) != NULL)
//	{
//		printf("%s", line);
//		free(line);
//	}
//	close(fd1);
//	while ((line = get_next_line(fd2)) != NULL)
//	{
//		printf("%s", line);
//		free(line);
//	}
//	close(fd2);

//	while ((line = get_next_line(fd3)) != NULL)
//	{
//		printf("%s", line);
//		free(line);
//	}
//	close(fd3);
//	return (0);
//}
