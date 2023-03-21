/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:24:36 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/21 07:54:00 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_slice(t_game *g, t_slice *slice)
{
	int	i;
	int	y_max = 1250;

	i = 0;
	while (i <= y_max)
	{
		if (i < slice->wall_start)
			my_mlx_pixel_put(g->img, slice->pos_x, i, g->t->fc[1]);
		else if (i >= slice->wall_start && i <= slice->wall_end)
			my_mlx_pixel_put(g->img, slice->pos_x, i, RED);
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
	int	x_max = 1920;				//screen res width
	int	y_max = 1250;				//screen res height
	int	i = 0;
	int	wall_size;
	t_pos	*p;
	t_slice	slice;


	g->img->img = mlx_new_image(g->mlx, 2000, 1500);
	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
	p = insert_rays(g);
	if (p->info->dist <= 0)
		p->info->dist = 1;
	wall_size = (y_max * 2) / (int)p->info->dist;
	slice.pos_x = 0;
	//int	lol = 0;				//debug
	/*while (p->info->next)
	{
		printf("ray ? %i\n\n", p->info->dist);
		p->info = p->info->next;
		lol++;
	}*/
	//printf("lol ---> %i\n\n\n", lol);
	while (i <= x_max)
	{
		slice.pos_x = i;
		draw_slice(g, &slice);
		if (!p->info->next)
			return ;
		p->info = p->info->next;
		if (p->info->dist <= 0)
			p->info->dist = 1;
		wall_size = (y_max * 4) / (int)p->info->dist;
		slice.wall_start = y_max / 2 - wall_size;
		slice.wall_end = y_max / 2 + wall_size;
		i+=4;
	}
	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
}
