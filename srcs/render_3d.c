// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   render_3d.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: leina <leina@student.42.fr>                +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/03/17 15:24:36 by bgrulois          #+#    #+#             */
// /*   Updated: 2023/04/06 16:36:17 by leina            ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../includes/cub3d.h"

int	eval_t_y(int y, int ws, double ratio)
{
	double	t_y;

	t_y = (double)(y - ws) / ratio;
	return ((int)t_y);
}


int	fix_ang_d(int a)
{
	printf("a = %d", a);
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	printf("a = %d", a);
	return (a);
}


t_data	*eval_tx_img(t_game *g, t_slice *slice)
{
	// printf("direct= %f\n", g->p->direction);
	if (slice->side == 0)
		return (&g->t->no_t);
	if (slice->side == 1)
		return (&g->t->so_t);
	if (slice->side == 2)
		return (&g->t->ea_t);
	if (slice->side == 3)
		return (&g->t->we_t);
	return (NULL);
}

void	draw_slice(t_game *g, t_slice *slice)
{
	int	y;
	double	ratio;
	int i;
	t_data	*tx;

	y = 0;
	ratio = (slice->wall_end - slice->wall_start) / TILE_SIZE_F;
	tx = eval_tx_img(g, slice);
	if (ratio <= 0.0)
		ratio = 0.01;
	while (y < RES_Y)
	{
		if (y < slice->wall_start)
			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[1]);
		else if (y > slice->wall_start && y <= slice->wall_end && slice->wall_pos != 0)
		{
			i = 0;
			while (i < 4)
			{
				g->img->addr[y * g->img->line_length + slice->pos_x * 4 + i] =
					tx->addr[eval_t_y(y, slice->wall_start, ratio)
					* g->t->so_t.line_length + (int)(slice->wall_pos) * 4 + i];
				i++;
			}
		}
		else if (y > slice->wall_end)
			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[0]);
		y++;
	}
}

void	init_slice(t_game *g, t_slice *slice, t_pos *p, int i)
{
	int	wall_size;
	(void)g;

	wall_size = ((RES_Y * TILE_SIZE) / p->info->dist);
	slice->pos_x = i;
	slice->wall_pos = ((p->info->pos_x + p->info->pos_y) % TILE_SIZE + 1);
	slice->wall_start = RES_Y / 2 - wall_size / 2;
	slice->wall_end = RES_Y / 2 + wall_size / 2;
	// if (fix_ang(p->rays) > 45 && fix_ang(p->rays) <= 135)
	// 	slice->side = 0;
	// else if (fix_ang(p->rays) > 135 && fix_ang(p->rays) <= 225)
	// 	slice->side = 1;
	// else if (fix_ang(p->rays) > 225 && fix_ang(p->rays) <= 315)
	// 	slice->side = 2;
	// else if (fix_ang_d(p->rays) > 315 && fix_ang_d(p->rays) <= 45)
	// 	slice->side = 3;
	slice->side = p->info->side;
	// if (p->info->side == 0)
	// 	slice->side = 0;
	// else
	// 	slice->side = 1;
	// if (p->info->side)
}

void	render_image(t_game *g)
{
	int	i;
	// t_pos	*p;
	t_slice	slice;

	i = 0;
	// p = g->pos;
	if (g->img->img)
		mlx_destroy_image(g->mlx, g->img->img);
	g->img->img = mlx_new_image(g->mlx, RES_X, RES_Y);
	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
	insert_rays(g);
	if (g->pos->info->dist <= 0)
		g->pos->info->dist = 1;
	init_slice(g, &slice, g->pos, i);
	draw_slice(g, &slice);
	while (++i < RES_X - 1)
	{
		if (!g->pos->info->next)
			return ;
		g->pos->info = g->pos->info->next;
		if (g->pos->info->dist == 0)
			g->pos->info->dist = 1;
		init_slice(g, &slice, g->pos, i);
		draw_slice(g, &slice);
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
	// free_rays_info(&g->pos->info);
	// free (g->pos);
	// g->pos = NULL;
}
