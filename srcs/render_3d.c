/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:24:36 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/30 04:19:20 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	eval_t_y(int y, int ws, float ratio)
{
	float	t_y;

	t_y = (float)(y - ws) / ratio;
	return ((int)t_y);
}

void	draw_slice(t_game *g, t_slice *slice)
{
	int	y;
	float	ratio;

	y = 0;
	ratio = (slice->wall_end - slice->wall_start) / TILE_SIZE_F;
	if (ratio == 0.0)
		ratio = 0.01;
	if (ratio < 1.0 && ratio > 0.0)
		ratio = 1.0 / ratio;
	//printf("\n$$$$$$$$$$$$$$$$$$\nTXT_XPOS(px) = %f\nRATIO = %f\n$$$$$$$$$$$$$$$$$$\n", slice->wall_pos, ratio);
	while (y < RES_Y)
	{
		if (y < slice->wall_start)
			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[1]);
		else if (y > slice->wall_start && y <= slice->wall_end && slice->wall_pos != 0)
		{
			g->img->addr[y * 4 * g->img->line_length / 4 + slice->pos_x * 4] =
				g->t->no_t.addr[eval_t_y(y, slice->wall_start, ratio)
				* g->t->no_t.line_length + (int)(slice->wall_pos * 4)];
		}
		else if (y > slice->wall_end)
			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[0]);
		y++;
	}
}

void	init_slice(t_slice *slice, t_pos *p, int i)
{
	int	wall_size;

	wall_size = ((RES_Y * TILE_SIZE) / (int)p->info->dist);
	slice->pos_x = i;
	slice->wall_pos = ((p->info->pos_x + p->info->pos_y) % TILE_SIZE) * 100.0 / TILE_SIZE_F;
	slice->wall_start = RES_Y / 2 - wall_size / 2;
	slice->wall_end = RES_Y / 2 + wall_size / 2;
	slice->wall_pos = slice->wall_pos * TILE_SIZE_F / 100.0;
}

void	render_image(t_game *g)
{
	int	i;
	t_pos	*p;
	t_slice	slice;

	i = 0;
	g->img->img = mlx_new_image(g->mlx, RES_X, RES_Y);
	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
	p = insert_rays(g);
	if (p->info->dist <= 0)
		p->info->dist = 1;
	init_slice(&slice, p, i);
	while (i < RES_X - 1)
	{
		if (!p->info->next)
			return ;
		p->info = p->info->next;
		if (p->info->dist <= 0)
			p->info->dist = 1;
		init_slice(&slice, p, i);
		draw_slice(g, &slice);
		i++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
}
