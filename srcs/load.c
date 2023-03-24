/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:53:19 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/24 18:08:41 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_textures(t_game *g)
{
	int	a;
	int	b;
	printf("floor color is : %i %i %i\n", g->t->f[0], g->t->f[1], g->t->f[2]);
	printf("ceiling color is : %i %i %i\n", g->t->c[0], g->t->c[1], g->t->c[2]);
	g->t->width = TEXTURE_WIDTH;
	g->t->height = TEXTURE_HEIGHT;
	g->t->no_t.img = mlx_xpm_file_to_image(g->mlx, g->m->no, &a, &b);
	if (a != TEXTURE_WIDTH || b != TEXTURE_HEIGHT || !g->t->no_t.img)
		return (1);
	g->t->so_t.img = mlx_xpm_file_to_image(g->mlx, g->m->so, &g->t->width, &g->t->height);
	if (a != TEXTURE_WIDTH || b != TEXTURE_HEIGHT || !g->t->no_t.img)
		return (1);
	g->t->ea_t.img = mlx_xpm_file_to_image(g->mlx, g->m->ea, &g->t->width, &g->t->height);
	if (a != TEXTURE_WIDTH || b != TEXTURE_HEIGHT || !g->t->no_t.img)
		return (1);
	g->t->we_t.img = mlx_xpm_file_to_image(g->mlx, g->m->we, &g->t->width, &g->t->height);
	if (a != TEXTURE_WIDTH || b != TEXTURE_HEIGHT || !g->t->no_t.img)
		return (1);
	g->t->no_t.addr = mlx_get_data_addr(g->t->no_t.img, &g->t->no_t.bits_per_pixel, &g->t->no_t.line_length, &g->t->no_t.endian);
	g->t->so_t.addr = mlx_get_data_addr(g->t->no_t.img, &g->t->no_t.bits_per_pixel, &g->t->no_t.line_length, &g->t->no_t.endian);
	g->t->ea_t.addr = mlx_get_data_addr(g->t->no_t.img, &g->t->no_t.bits_per_pixel, &g->t->no_t.line_length, &g->t->no_t.endian);
	g->t->we_t.addr = mlx_get_data_addr(g->t->no_t.img, &g->t->no_t.bits_per_pixel, &g->t->no_t.line_length, &g->t->no_t.endian);
	return (0);
}
