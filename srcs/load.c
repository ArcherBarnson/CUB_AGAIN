/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:53:19 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/30 09:57:20 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_textures_addr(t_game *g)
{
	g->t->no_t.addr = mlx_get_data_addr(g->t->no_t.img,
			&g->t->no_t.bits_per_pixel,
			&g->t->no_t.line_length,
			&g->t->no_t.endian);
	g->t->so_t.addr = mlx_get_data_addr(g->t->so_t.img,
			&g->t->so_t.bits_per_pixel,
			&g->t->so_t.line_length,
			&g->t->so_t.endian);
	g->t->ea_t.addr = mlx_get_data_addr(g->t->ea_t.img,
			&g->t->ea_t.bits_per_pixel,
			&g->t->ea_t.line_length,
			&g->t->ea_t.endian);
	g->t->we_t.addr = mlx_get_data_addr(g->t->we_t.img,
			&g->t->we_t.bits_per_pixel,
			&g->t->we_t.line_length,
			&g->t->we_t.endian);
}

int	load_textures(t_game *g)
{
	int	a;
	int	b;

	g->t->width = TEXTURE_WIDTH;
	g->t->height = TEXTURE_HEIGHT;
	g->t->no_t.img = mlx_xpm_file_to_image(g->mlx, g->m->no, &a, &b);
	if (a != TEXTURE_WIDTH || b != TEXTURE_HEIGHT || !g->t->no_t.img)
		return (1);
	g->t->so_t.img = mlx_xpm_file_to_image(g->mlx,
			g->m->so, &g->t->width,
			&g->t->height);
	if (a != TEXTURE_WIDTH || b != TEXTURE_HEIGHT || !g->t->no_t.img)
		return (1);
	g->t->ea_t.img = mlx_xpm_file_to_image(g->mlx,
			g->m->ea, &g->t->width,
			&g->t->height);
	if (a != TEXTURE_WIDTH || b != TEXTURE_HEIGHT || !g->t->no_t.img)
		return (1);
	g->t->we_t.img = mlx_xpm_file_to_image(g->mlx,
			g->m->we, &g->t->width,
			&g->t->height);
	if (a != TEXTURE_WIDTH || b != TEXTURE_HEIGHT || !g->t->no_t.img)
		return (1);
	get_textures_addr(g);
	return (0);
}
