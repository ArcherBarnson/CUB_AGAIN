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

// int	eval_t_y(int y, int ws, double ratio)
// {
// 	double	t_y;

// 	t_y = (double)(y - ws) / ratio;
// 	return ((int)t_y);
// }
// /*
// t_data	*eval_tx_img(t_game *g, t_slice *slice)
// {
// 	if (slice->side == 0)
// 		return (&g->t->no_t);
// 	if (slice->side == 1)
// 		return (&g->t->we_t);
// 	if (slice->side == 2)
// 		return (&g->t->so_t);
// 	if (slice->side == 3)
// 		return (&g->t->ea_t);
// 	return (NULL);
// }
// */
// void	draw_slice(t_game *g, t_slice *slice)
// {
// 	int	y;
// 	double	ratio;
// 	int i;
// 	//t_data	*tx;

// 	y = 0;
// 	ratio = (slice->wall_end - slice->wall_start) / TILE_SIZE_F;
// 	//tx = eval_tx_img(g, slice);
// 	if (ratio <= 0.0)
// 		ratio = 0.01;
// 	/*if (ratio < 1.0 && ratio > 0.0)
// 		ratio = 1.0 / ratio;*/
// 	//printf("\n$$$$$$$$$$$$$$$$$$\nTXT_XPOS(px) = %f\nRATIO = %f\n$$$$$$$$$$$$$$$$$$\n", slice->wall_pos, ratio);
// 	while (y < RES_Y)
// 	{
// 		if (y < slice->wall_start)
// 			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[1]);
// 		else if (y > slice->wall_start && y <= slice->wall_end && slice->wall_pos != 0)
// 		{
// 			i = 0;
// 			while (i < 4)
// 			{
// 				g->img->addr[y * g->img->line_length + slice->pos_x * 4 + i] =
// 					g->t->so_t.addr[eval_t_y(y, slice->wall_start, ratio)
// 					* g->t->so_t.line_length + (int)(slice->wall_pos) * 4 + i];
// 				i++;
// 			}
// 		}
// 		else if (y > slice->wall_end)
// 			my_mlx_pixel_put(g->img, slice->pos_x, y, g->t->fc[0]);
// 		y++;
// 	}
// }

// void	init_slice(t_game *g, t_slice *slice, t_pos *p, int i)
// {
// 	int	wall_size;

// 	wall_size = ((RES_Y * TILE_SIZE) / (int)p->info->dist);
// 	slice->pos_x = i;
// 	slice->wall_pos = ((p->info->pos_x + p->info->pos_y) % TILE_SIZE) * 100.0 / TILE_SIZE_F;
// 	slice->wall_start = RES_Y / 2 - wall_size / 2;
// 	slice->wall_end = RES_Y / 2 + wall_size / 2;
// 	slice->wall_pos = slice->wall_pos * TILE_SIZE_F / 100.0;
// 	if (p->info->wich_rays > 300)
// 		slice->side = (int)((g->p->direction * 10.0) + ((double)p->info->wich_rays) / 10.0);
// 	else if (p->info->wich_rays < 300)
// 		slice->side = (int)((g->p->direction * 10.0) - ((double)p->info->wich_rays) / 10.0);
// 	else
// 		slice->side = (int)g->p->direction;
// 	slice->side /= 900;
// 	///UN PEU NUL TT CA
// 	printf("!! side = %i!! \n", slice->side);

// }

// void	render_image(t_game *g)
// {
// 	int	i;
// 	t_pos	*p;
// 	t_slice	slice;

// 	i = 0;
// 	if (g->img->img)
// 		mlx_destroy_image(g->mlx, g->img->img);
// 	g->img->img = mlx_new_image(g->mlx, RES_X, RES_Y);
// 	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
// 	p = insert_rays(g);
// 	if (p->info->dist <= 0)
// 		p->info->dist = 1;
// 	init_slice(g, &slice, p, i);
// 	draw_slice(g, &slice);
// 	while (i < RES_X - 1)
// 	{
// 		if (!p->info->next)
// 			return ;
// 		p->info = p->info->next;
// 		if (p->info->dist <= 0)
// 			p->info->dist = 1;
// 		init_slice(g, &slice, p, i);
// 		draw_slice(g, &slice);
// 		i++;
// 	}
// 	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
// }


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


t_data	*eval_tx_img(t_game *g)
{
	printf("direct= %f\n", g->p->direction);
	if (fix_ang(g->p->direction) > 45 && fix_ang(g->p->direction) <= 135)
		return (&g->t->no_t);
	if (fix_ang(g->p->direction) > 135 && fix_ang(g->p->direction) <= 225)
		return (&g->t->we_t);
	if (fix_ang(g->p->direction) > 225 && fix_ang(g->p->direction) <= 315)
		return (&g->t->so_t);
	if (fix_ang_d(g->p->direction) > 315 && fix_ang_d(g->p->direction) <= 45)
		return (&g->t->ea_t);
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
	// if (slice->side == 0)
	// 	tx = &g->t->no_t;
	// else if (slice->side == 1)
	// 	tx = &g->t->so_t;
	tx = eval_tx_img(g);
	if (ratio <= 0.0)
		ratio = 0.01;
	/*if (ratio < 1.0 && ratio > 0.0)
		ratio = 1.0 / ratio;*/
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
	if (p->info->side == 0)
		slice->side = 0;
	else
		slice->side = 1;
	///UN PEU NUL TT CA
	//printf("!! side = %i!! \n", slice->side);

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
	while (++i < RES_X - 1)
	{
		if (!p->info->next)
			return ;
		p->info = p->info->next;
		//if (p->info->side == 0)
		if (p->info->dist == 0)
			p->info->dist = 1;
		init_slice(g, &slice, p, i);
		draw_slice(g, &slice);
	}
		printf("p->x %d p->y %d perx %f per y%f\n", p->info->pos_x, p->info->pos_y, g->p->x, g->p->y);
	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
}


// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   render_3d.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/03/17 15:24:36 by bgrulois          #+#    #+#             */
// /*   Updated: 2023/03/22 18:37:19 by bgrulois         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/cub3d.h"

// void	draw_slice(t_game *g, t_slice *slice, int color)
// {
// 	int	i;
// 	int	y_max = 720;

// 	i = 0;
// 	while (i <= y_max)
// 	{
// 		if (i < slice->wall_start)
// 			my_mlx_pixel_put(g->img, slice->pos_x, i, g->t->fc[1]);
// 		else if (i >= slice->wall_start && i <= slice->wall_end)
// 			my_mlx_pixel_put(g->img, slice->pos_x, i, color);
// 		else if (i > slice->wall_end)
// 			my_mlx_pixel_put(g->img, slice->pos_x, i, g->t->fc[0]);
// 		i++;
// 	}
// }

// void	render_image(t_game *g)
// {
// 	int	x_max = RES_X;				//screen res width
// 	int	y_max = RES_Y;				//screen res height
// 	int	i = 0;
// 	int	wall_size;
// 	int	fisheye_fix;
// 	int	color = RED;
// 	t_pos	*p;
// 	t_slice	slice;


// 	g->img->img = mlx_new_image(g->mlx, RES_X, RES_Y);
// 	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
// 	p = insert_rays(g);
// 	if (p->info->dist <= 0)
// 		p->info->dist = 1;
// 	fisheye_fix = x_max / tan(deg_to_rad(30));
// 	wall_size = (((y_max * 2) / (int)p->info->dist) / ((int)p->info->dist)) * (fisheye_fix);
// 	slice.pos_x = 0;
// 	while (i < x_max - 1)
// 	{
// 		if (p->info->side)
// 			color = RED;
// 		else
// 			color = TEST_2;
// 		slice.pos_x = i;
// 		draw_slice(g, &slice, color);
// 		if (!p->info->next)
// 			return ;
// 		p->info = p->info->next;
// 		if (p->info->dist <= 0)
// 			p->info->dist = 1;
// 		wall_size = ((y_max * TILE_SIZE) / (int)p->info->dist);
// 		slice.wall_start = y_max / 2 - wall_size / 2;
// 		slice.wall_end = y_max / 2 + wall_size / 2;
// 		i++;
// 	}
// 	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
// }
