/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lteng <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 11:29:57 by lteng             #+#    #+#             */
/*   Updated: 2024/05/18 14:34:00 by lteng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Allowed functions: read, free, malloc

Write a function named get_next_line which prototype should be:
char	*get_next_line(int fd);

Your function must return a line that has been read from the file descriptor passed as parameter.
What we call a "line that has been read" is a succession of 0 to n characters that end with '\n' (ascii code 0x0a) or with End Of File (EOF).

The line should be returned including the '\n' in case there is one at the end of the line that has been read.
When you've reached the EOF,
you must store the current buffer in a char* and return it. If the buffer is empty you must return NULL.

In case of error return NULL. In case of not returning NULL,the pointer should be free-able.
Your program will be compiled with the flag-D BUFFER_SIZE=xx,which has to be used as the buffer size for the read calls in your functions.

Your function must be memory leak free. When you've reached the EOF,your function should keep 0 memory allocated with malloc,except the line that has been returned.

Calling your function get_next_line() in a loop will therefore allow you to read the text available on a file descriptor one line at a time until the end of the text,
no matter the size of either the text or one of its lines.

Make sure that your function behaves well when it reads from a file,
from the standard output, from a redirection, etc...

No call to another function will be done on the file descriptor between 2 calls of get_next_line(). Finally we consider that get_next_line() has an undefined behaviour when reading from a binary file.
*/

/*
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif
*/

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[9999999] = {'\0'};
	static int	i = 0;
	int			j;
	int			read_byte;
	char		*line;

	j = 0;
	read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, &buffer[j], BUFFER_SIZE);
		if (read_byte == -1 || buffer[i] == '\0')
			return (NULL);
		j += read_byte;
	}
	read_byte = 0;
	while (buffer[i + read_byte] != '\0' && buffer[i + read_byte] != '\n')
		read_byte++;
	line = malloc(read_byte + 1 + (buffer[i + read_byte] == '\n'));
	if (!line)
		return (NULL);
	line[read_byte + (buffer[i + read_byte] == '\n')] = '\0';
	j = 0;
	while (j <= read_byte)
		line[j++] = buffer[i++];
	return (line);
}

/*
int	main(void)
{
	int fd;
	int i;
	char *a;

	fd = open("test.txt", O_RDONLY);
	i = 0;
	while (i < 4)
	{
		a = get_next_line(fd);
		printf("%s", a);
		free(a);
		i++;
	}
	return (0);
}*/