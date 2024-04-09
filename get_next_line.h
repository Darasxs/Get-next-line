/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaluszk <dpaluszk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 12:51:31 by dpaluszk          #+#    #+#             */
/*   Updated: 2024/04/09 18:34:11 by dpaluszk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE.H
# define GET_NEXT_LINE .H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 42

# include <unistd.h>
# include <stdio.h>

char	*get_next_line(int fd);

#endif