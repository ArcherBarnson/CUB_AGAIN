/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 09:49:50 by bgrulois          #+#    #+#             */
/*   Updated: 2023/02/27 10:25:11 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cleanstr(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		buf[i] = '\0';
		i++;
	}
}

void	rearrange(char *buf, int size)
{
	int	i;
	int	j;

	i = 0;
	size++;
	j = ft_strlen(buf) - size;
	while (i < j)
	{
		buf[i] = buf[size + i];
		i++;
	}
	buf[i] = '\0';
}

char	*strdupmod(char *src, char *dest)
{
	int	i;

	i = 0;
	while (src[i] != '\n' && src[i])
		i++;
	if (src[i] == '\n')
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] != '\n' && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*read_and_check(int fd, char *buf)
{
	int	read_val;

	if (buf[0] == '\0')
	{
		read_val = read(fd, buf, BUFFER_SIZE);
		if (read_val <= 0)
			return (NULL);
		buf[read_val] = '\0';
	}
	return (buf);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*returnstr;

	returnstr = NULL;
	if (read_and_check(fd, buf) == NULL)
		return (NULL);
	if (BUFFER_SIZE == 0)
		return (NULL);
	if (line_is_full(buf) != 0)
	{
		returnstr = strdupmod(buf, returnstr);
		rearrange(buf, get_line_size(buf));
	}
	else if (line_is_full(buf) == 0)
	{
		returnstr = strdupmod(buf, returnstr);
		cleanstr(buf);
		return (malloc_free_cat(returnstr, get_next_line(fd)));
	}
	return (returnstr);
}
