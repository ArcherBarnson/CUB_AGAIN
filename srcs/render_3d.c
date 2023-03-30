/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:24:36 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/30 13:46:40 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	eval_t_y(int y, int ws, double ratio)
{
	double	t_y;

	t_y = (double)(y - ws) / ratio;
	return ((int)t_y);
}
/*
t_data	*eval_tx_img(t_game *g, t_slice *slice)
{
	if (slice->side == 0)
		return (&g->t->no_t);
	if (slice->side == 1)
		return (&g->t->we_t);
	if (slice->side == 2)
		return (&g->t->so_t);
	if (slice->side == 3)
		return (&g->t->ea_t);
	return (NULL);
}
*/
void	draw_slice(t_game *g, t_slice *slice)
{
	int	y;
	double	ratio;
	int i;
	//t_data	*tx;

	y = 0;
	ratio = (slice->wall_end - slice->wall_start) / TILE_SIZE_F;
	//tx = eval_tx_img(g, slice);
	if (ratio <= 0.0)
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
			i = 0;
			while (i < 4)
			{
				g->img->addr[y * g->img->line_length + slice->pos_x * 4 + i] =
					g->t->so_t.addr[eval_t_y(y, slice->wall_start, ratio)
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

	wall_size = ((RES_Y * TILE_SIZE) / (int)p->info->dist);
	slice->pos_x = i;
	slice->wall_pos = ((p->info->pos_x + p->info->pos_y) % TILE_SIZE) * 100.0 / TILE_SIZE_F;
	slice->wall_start = RES_Y / 2 - wall_size / 2;
	slice->wall_end = RES_Y / 2 + wall_size / 2;
	slice->wall_pos = slice->wall_pos * TILE_SIZE_F / 100.0;
	if (p->info->wich_rays > 300)
		slice->side = (int)((g->p->direction * 10.0) + ((double)p->info->wich_rays) / 10.0);
	else if (p->info->wich_rays < 300)
		slice->side = (int)((g->p->direction * 10.0) - ((double)p->info->wich_rays) / 10.0);
	else
		slice->side = (int)g->p->direction;
	slice->side /= 900;
	///UN PEU NUL TT CA
	printf("!! side = %i!! \n", slice->side);

}

void	render_image(t_game *g)
{
	int	i;
	t_pos	*p;
	t_slice	slice;

	i = 0;
	if (g->img->img)
		mlx_destroy_image(g->mlx, g->img->img);
	g->img->img = mlx_new_image(g->mlx, RES_X, RES_Y);
	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
	p = insert_rays(g);
	if (p->info->dist <= 0)
		p->info->dist = 1;
	init_slice(g, &slice, p, i);
	draw_slice(g, &slice);
	while (i < RES_X - 1)
	{
		if (!p->info->next)
			return ;
		p->info = p->info->next;
		if (p->info->dist <= 0)
			p->info->dist = 1;
		init_slice(g, &slice, p, i);
		draw_slice(g, &slice);
		i++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
}
