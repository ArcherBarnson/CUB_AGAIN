/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:24:36 by bgrulois          #+#    #+#             */
/*   Updated: 2023/04/12 16:54:21 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_slice(t_game *g, t_slice *slice)
{
	int		y;
	double	ratio;

	y = 0;
	ratio = (slice->wall_end - slice->wall_start) / TILE_SIZE_F;
	if (ratio <= 0.0)
		ratio = 0.01;
	while (y < RES_Y)
	{
		if (y < slice->wall_start)
			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[1]);
		else if (y > slice->wall_start && y <= slice->wall_end
			&& slice->wall_pos != 0)
			eval_t_color(g, slice, y, ratio);
		else if (y > slice->wall_end)
			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[0]);
		y++;
	}
}

void	init_slice(t_slice *slice, t_pos *p, int i)
{
	int	wall_size;

	wall_size = ((RES_X * TILE_SIZE) / p->info->dist);
	slice->pos_x = i;
	slice->wall_pos = ((p->info->pos_x + p->info->pos_y) % TILE_SIZE + 1);
	slice->wall_start = RES_Y / 2 - wall_size / 2;
	slice->wall_end = RES_Y / 2 + wall_size / 2;
	slice->side = p->info->side;
}

void	draw_image(t_game *g, t_slice *slice)
{
	int	i;

	i = 0;
	while (++i < RES_X)
	{
		if (!g->pos->info->next)
			return ;
		g->pos->info = g->pos->info->next;
		if (g->pos->info->dist == 0)
			g->pos->info->dist = 1;
		init_slice(slice, g->pos, i);
		draw_slice(g, slice);
	}
}

void	render_image(t_game *g)
{
	t_slice	slice;

	g->img->img = NULL;
	if (g->img->img)
		mlx_destroy_image(g->mlx, g->img->img);
	g->img->img = mlx_new_image(g->mlx, RES_X, RES_Y);
	g->img->addr = mlx_get_data_addr(g->img->img,
			&g->img->bits_per_pixel,
			&g->img->line_length,
			&g->img->endian);
	insert_rays(g);
	if (g->pos->info->dist <= 0)
		g->pos->info->dist = 1;
	init_slice(&slice, g->pos, 0);
	draw_slice(g, &slice);
	draw_image(g, &slice);
	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
	free_rays_info(g->pos->info);
	free (g->pos);
	g->pos = NULL;
}
