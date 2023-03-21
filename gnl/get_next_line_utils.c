/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 17:25:30 by bgrulois          #+#    #+#             */
/*   Updated: 2023/02/27 10:24:57 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h" 

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	get_line_size(char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (0);
	while (buf[i] && buf[i] != '\n')
		i++;
	return (i);
}

int	line_is_full(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (ft_strlen(buf) - i);
		i++;
	}
	return (0);
}

char	*malloc_free_cat(char *returnstr, char *newbuf)
{
	int		i;
	int		j;
	int		size;
	char	*newstr;

	i = 0;
	j = -1;
	size = ft_strlen(returnstr) + ft_strlen(newbuf);
	newstr = malloc(sizeof(char) * (size + 1));
	if (!newstr)
		return (NULL);
	while (returnstr[++j])
		newstr[j] = returnstr[j];
	free(returnstr);
	while (newbuf && newbuf[i])
	{
		newstr[j] = newbuf[i];
		i++;
		j++;
	}
	free(newbuf);
	newstr[j] = '\0';
	return (newstr);
}
