/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarra <gmarra@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:34:30 by gmarra            #+#    #+#             */
/*   Updated: 2024/12/22 16:31:22 by gmarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	copy_buffer(char *buffer, char **str_out, ssize_t bytes,
		ssize_t bytes_read)
{
	size_t	len;

	if (bytes > bytes_read)
		bytes = bytes_read;
	if (bytes > 0 && buffer[0] != '\0')
	{
		len = ft_strlen(*str_out);
		*str_out = ft_realloc(*str_out, len, len + bytes + 1, sizeof(char));
		ft_memmove (*str_out + len, buffer, bytes);
		(*str_out)[bytes + len] = '\0';
		buffer_shift(buffer, bytes);
	}
}

static void	free_all(t_buffer_fd *buffer_fd, char **str_out, int status)
{
	if (status == -1 || (status == 1 && !**str_out))
	{
		free(buffer_fd->buff);
		buffer_fd->buff = NULL;
		free(*str_out);
		*str_out = NULL;
		buffer_fd->fd = -1;
	}
}

static int	run_char_search(t_buffer_fd *buffer_fd,
			char **str_out, char separator)
{
	ssize_t	i;
	ssize_t	flg_finish;

	i = 0;
	flg_finish = 0;
	if (!buffer_fd->read_bytes && buffer_fd->buff[0] == 0)
	{
		buffer_fd->read_bytes = read(buffer_fd->fd, buffer_fd->buff,
				BUFFER_SIZE);
		if (buffer_fd->read_bytes < 0)
			return (-1);
		else if (!buffer_fd->read_bytes && *str_out)
			return (1);
	}
	while (i < buffer_fd->read_bytes && !flg_finish && buffer_fd->buff[i] != 0)
		if (buffer_fd->buff[i++] == separator)
			flg_finish = 1;
	copy_buffer(buffer_fd->buff, str_out, i, buffer_fd->read_bytes);
	if (i >= buffer_fd->read_bytes && !flg_finish)
		return (buffer_fd->read_bytes = 0, flg_finish);
	return (buffer_fd->read_bytes -= i, flg_finish);
}

char	*get_next_line(int fd)
{
	char				*read_line;
	int					finish;
	static t_buffer_fd	buffer_fd[FD_SETSIZE] = {[0] = {.fd = -1}};

	finish = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || buffer_fd[fd].read_bytes < 0)
		return (NULL);
	if (buffer_fd[fd].fd != fd && !buffer_fd[fd].buff)
	{
		buffer_fd[fd].fd = fd;
		buffer_fd[fd].buff = (char *) malloc(BUFFER_SIZE);
		if (!buffer_fd[fd].buff)
			return (NULL);
		ft_memset(buffer_fd[fd].buff, 0, BUFFER_SIZE);
	}
	read_line = (char *) malloc(1 * sizeof (char));
	if (!read_line)
		return (free_all(&buffer_fd[fd], &read_line, 0), NULL);
	read_line[0] = '\0';
	while (!finish && buffer_fd[fd].read_bytes >= 0)
		finish = run_char_search(&buffer_fd[fd], &read_line, SEPARATOR);
	free_all(&buffer_fd[fd], &read_line, finish);
	if (!read_line)
		return (NULL);
	return (read_line);
}
