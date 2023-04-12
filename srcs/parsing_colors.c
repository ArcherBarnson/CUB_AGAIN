/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:58:40 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/15 18:53:03 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_color_code(char *id, int i)
{
	int		n;
	int		size;
	char	*nb;

	n = -1;
	size = 0;
	nb = NULL;
	if (!id || id[i] == '\0' || id[i] > '9' || id[i] < '0')
		return (-1);
	while (id[size + i] && id[size + i] <= '9' && id[size + i] >= '0')
		size++;
	if (size > 3)
		return (-1);
	nb = malloc(sizeof(char) * (size + 1));
	if (!nb)
		return (-1);
	nb[size] = '\0';
	size = -1;
	i--;
	while (id[++i] && id[i] <= '9' && id[i] >= '0')
		nb[++size] = id[i];
	n = ft_atoi(nb);
	if (nb)
		free(nb);
	return (n);
}

int	skip_color_code(char *tile, int i)
{
	if (!tile || !tile[i])
		return (i);
	while (tile[i] <= '9' && tile[i] >= '0')
		i++;
	while (tile[i] == ',' && (tile[i] > '9' || tile[i] < '0'))
		i++;
	if (tile[i] > '9' || tile[i] < '0')
		return (-1);
	return (i);
}

int	get_hex_color(int rgb[3])
{
	int	color;

	color = (rgb[0] << 16) + (rgb[1] << 8) + (rgb[2]);
	return (color);
}

int	get_rgb(char *tile, int color)
{
	int	i;
	int	n;

	i = 0;
	n = -1;
	while (tile && tile[i] && tile[i] != ' ')
		i++;
	while (tile && tile[i] && tile[i] == ' ')
		i++;
	if (color == 2 && tile && tile[i])
	{
		i = skip_color_code(tile, i);
		i = skip_color_code(tile, i);
		n = get_color_code(tile, i);
	}
	if (color == 1 && tile && tile[i])
	{
		i = skip_color_code(tile, i);
		n = get_color_code(tile, i);
	}
	if (color == 0 && tile && tile[i])
		n = get_color_code(tile, i);
	if (n < 0 || n > 255)
		return (-1);
	return (n);
}
