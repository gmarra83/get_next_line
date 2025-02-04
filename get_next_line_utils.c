/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarra <gmarra@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:22:05 by gmarra            #+#    #+#             */
/*   Updated: 2024/12/22 16:33:38 by gmarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*mem_addr;
	char	*mem_src;

	mem_addr = (char *)dest;
	mem_src = (char *)src;
	if (!dest || !src)
		return (NULL);
	if (mem_src < mem_addr)
		while (n--)
			*(mem_addr + n) = *(mem_src + n);
	else
		while (n--)
			*mem_addr++ = *mem_src++;
	return (dest);
}

void	ft_memset(void *s, int c, size_t n)
{
	unsigned char	byte2set;
	unsigned char	*mem_addr;

	byte2set = (unsigned char) c;
	mem_addr = (unsigned char *)s;
	while (n)
		mem_addr[--n] = byte2set;
}

void	*ft_realloc(void *array, size_t curr_dim, size_t new_dim,
			size_t elem_dim)
{
	unsigned char	*new_arr;

	if (!new_dim || !elem_dim || curr_dim == new_dim)
		return (array);
	if (curr_dim > new_dim)
		curr_dim = new_dim;
	new_arr = (unsigned char *) malloc(new_dim * elem_dim);
	if (!new_arr)
		return (array);
	ft_memset(new_arr, 0, new_dim * elem_dim);
	ft_memmove(new_arr, array, curr_dim * elem_dim);
	free (array);
	return (new_arr);
}

void	buffer_shift(void *buffer, ssize_t bytes)
{
	ssize_t		i;

	if (bytes >= BUFFER_SIZE)
	{
		ft_memset(buffer, 0, BUFFER_SIZE);
		return ;
	}
	i = BUFFER_SIZE - bytes;
	ft_memmove(buffer, (buffer + bytes), i);
	ft_memset(buffer + i, 0, bytes);
}

size_t	ft_strlen(const char *str)
{
	size_t	lenstr;

	lenstr = 0;
	while (*str)
	{
		lenstr++;
		str++;
	}
	return (lenstr);
}
