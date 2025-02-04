/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarra <gmarra@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:15:29 by gmarra            #+#    #+#             */
/*   Updated: 2024/12/18 17:30:28 by gmarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef SEPARATOR
#  define SEPARATOR '\n'
# endif

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/select.h>

typedef struct s_buffer
{
	int		fd;
	char	*buff;
	ssize_t	read_bytes;
}	t_buffer_fd;

void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_realloc(void *array, size_t curr_dim, size_t new_dim,
			size_t elem_dim);
void	buffer_shift(void *buffer, ssize_t bytes);
size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
void	ft_memset(void *s, int c, size_t n);

#endif
