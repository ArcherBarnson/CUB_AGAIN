/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:24:36 by bgrulois          #+#    #+#             */
/*   Updated: 2023/04/04 13:32:16 by lcorpora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// void	draw_slice(t_game *g, t_slice *slice)
// {
// 	int	y;
// 	int	color;

// 	y = 0;
// 	//Formule pour char *addr : X position * 4 + 4 * Line size * Y position. (Merci à grezette)
// 	color = g->t->no_t.addr[y * g->t->no_t.line_length / 4 + slice->pos_x];
// 	while (y < RES_Y)
// 	{
// 		if (y < slice->wall_start)
// 			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[1]);
// 		else if (y >= slice->wall_start && y <= slice->wall_end)
// 			my_mlx_pixel_put(g->img, slice->pos_x, y, color);
// 		else if (y > slice->wall_end)
// 			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[0]);
// 		color = slice->pos_x * 4 + 4 * g->t->no_t.line_length * y;
// 		//color = g->t->no_t.addr[y * g->t->no_t.line_length / 4 + slice->pos_x];
// 		y++;
// 	}
// }

// /*
// void	fill_image(t_game *g)				//debug funct
// {
// 	int	i = 0;
// 	int	j = 0;

// 	while (i < RES_X)
// 	{
// 		while (j < RES_Y)
// 		{
// 			my_mlx_pixel_put(g->img, j, i, g->t->fc[0]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return ;
// }
// */

// void	render_image(t_game *g)
// {
// 	int	i;
// 	int	wall_size;
// 	t_pos	*p;
// 	t_slice	slice;

// 	i = 0;
// 	g->img->img = mlx_new_image(g->mlx, RES_X, RES_Y);
// 	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
// 	p = insert_rays(g);
// 	if (p->info->dist <= 0)
// 		p->info->dist = 1;
// 	wall_size = ((RES_Y * TILE_SIZE) / (int)p->info->dist);
// 	slice.pos_x = 0;
// 	while (i < RES_X - 1)
// 	{
// 		slice.pos_x = i;
// 		draw_slice(g, &slice);
// 		if (!p->info->next)
// 			return ;
// 		p->info = p->info->next;
// 		if (p->info->dist <= 0)
// 			p->info->dist = 1;
// 		wall_size = ((RES_Y * TILE_SIZE) / (int)p->info->dist);
// 		slice.wall_start = RES_Y / 2 - wall_size / 2;
// 		slice.wall_end = RES_Y / 2 + wall_size / 2;
// 		i++;
// 	}
// 	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
// }


void	draw_slice(t_game *g, t_slice *slice, int color)
{
	int	i;
	int	y_max = 720;

	i = 0;
	while (i <= y_max)
	{
		if (i < slice->wall_start)
			my_mlx_pixel_put(g->img, slice->pos_x, i, g->t->fc[1]);
		else if (i >= slice->wall_start && i <= slice->wall_end)
			my_mlx_pixel_put(g->img, slice->pos_x, i, color);
		else if (i > slice->wall_end)
			my_mlx_pixel_put(g->img, slice->pos_x, i, g->t->fc[0]);
		i++;
	}
}

/*
void	fill_image(t_game *g)				//debug funct
{
	int	x_max = 1080;
	int	y_max = 720;
	int	i = 0;
	int	j = 0;
	while (i < x_max)
	{
		while (j < y_max)
		{
			my_mlx_pixel_put(g->img, j, i, g->t->fc[0]);
			j++;
		}
		i++;
	}
	return ;
}
*/

void	render_image(t_game *g)
{
	int	x_max = RES_X;				//screen res width
	int	y_max = RES_Y;				//screen res height
	int	i = 0;
	int	wall_size;
	int	fisheye_fix;
	int	color = RED;
	t_pos	*p;
	t_slice	slice;


	g->img->img = mlx_new_image(g->mlx, RES_X, RES_Y);
	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
	p = insert_rays(g);
	if (p->info->dist <= 0)
		p->info->dist = 1;
	//printf("wall_size = %i\n", wall_size);
	fisheye_fix = x_max / tan(deg_to_rad(30));
	wall_size = (((y_max * 2) / (int)p->info->dist) / ((int)p->info->dist)) * (fisheye_fix);
	slice.pos_x = 0;
	/*int	lol = 0;				//debug
	while (p->info->next)
	{
		//printf("ray ? %i\n\n", p->info->dist);
		p->info = p->info->next;
		lol++;
	}
	printf("lol ---> %i\n\n\n", lol);*/
	while (i < x_max - 1)
	{
		//double	test = (60 / (x_max - 1) * i) + (double)((double)g->p->direction - 30);
		//if (test < 0)
		//	test += 360 * M_PI / 180;
		//double	fi = g->p->direction - test;
		//if (fi < 0)
		//	fi += M_PI;
		//else if (fi > M_PI)
		//	fi -= M_PI;
		if (p->info->side == 1)
			color = RED;
		else
			color = TEST_2;
		slice.pos_x = i;
		draw_slice(g, &slice, color);
		if (!p->info->next)
			return ;
		p->info = p->info->next;
		if (p->info->dist <= 0)
			p->info->dist = 1;
		wall_size = ((y_max * TILE_SIZE) / (int)p->info->dist);
		//wall_size = (TILE_SIZE / (int)p->info->dist) * fisheye_fix;
		//double k = 2000 / wall_size;
		//double k = wall_size;
		slice.wall_start = y_max / 2 - wall_size / 2;
		slice.wall_end = y_max / 2 + wall_size / 2;
		//slice.wall_start = y_max / 2 - wall_size;
		//slice.wall_end = y_max / 2 + wall_size;
		i++;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
}
