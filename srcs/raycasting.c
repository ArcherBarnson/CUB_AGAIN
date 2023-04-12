/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leina <leina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:06:38 by lcorpora          #+#    #+#             */
/*   Updated: 2023/04/11 13:00:44 by leina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	rays_dist_hori(t_pos *p, t_game *g)
{
	while (1 && p->hori_x >= 0 && p->hori_y >= 0)
	{
		p->map_x = (p->hori_x / TILE_SIZE_F);
		p->map_y = (p->hori_y / TILE_SIZE_F);
		p->map_p = p->map_x * 10 + p->map_y;
		if (p->map_y < 0 || (p->map_p > 0 && (p->map_y >= p->len_y
					|| (p->map_y < p->len_y && p->map_x
						>= ft_strlen(g->m->map[p->map_y]) - 1))))
			return ;
		if (p->map_p >= 0 && p->map_x < ft_strlen(g->m->map[p->map_y]) - 1
			&& p->map_y <= p->len_y && g->m->map[p->map_y][p->map_x] == 49)
		{
			p->dist_hori = sqrt(pow((int)g->p->x - p->hori_x, 2) \
				+ pow((int)g->p->y - p->hori_y, 2));
			return ;
		}
		p->hori_x += p->add_x;
		p->hori_y += p->add_y;
	}
}

void	rays_dist_verti(t_pos *p, t_game *g)
{
	while (1 && p->verti_x >= 0 && p->verti_y >= 0)
	{
		p->map_x = (p->verti_x / TILE_SIZE);
		p->map_y = (p->verti_y / TILE_SIZE);
		p->map_p = p->map_x * 10 + p->map_y;
		if (p->map_p > 0 && (p->map_y >= p->len_y
				|| (p->map_y < p->len_y && p->map_x
					>= ft_strlen(g->m->map[p->map_y]) - 1)))
			return ;
		if (p->map_p >= 0 && p->map_x < ft_strlen(g->m->map[p->map_y]) - 1
			&& p->map_y <= p->len_y && g->m->map[p->map_y][p->map_x] == 49)
		{
			p->dist_verti = sqrt(pow((int)g->p->x - p->verti_x, 2) \
				+ pow((int)g->p->y - p->verti_y, 2));
			return ;
		}
		p->verti_x += p->add_x;
		p->verti_y += p->add_y;
	}
}

void	check_horizontal(t_pos *p, t_game *g)
{
	p->add_x = TILE_SIZE;
	p->map_p = 10;
	p->add_y = TILE_SIZE * (tan(deg_to_rad(p->rays)));
	if (p->rays > 90 && p->rays < 270)
	{
		p->hori_x = ((int)g->p->x / TILE_SIZE) * TILE_SIZE - 0.001;
		p->hori_y = ((int)g->p->x - p->hori_x) * p->tan + (int)g->p->y;
		p->add_x *= -1;
	}
	else
	{
		p->hori_x = ((int)g->p->x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		p->hori_y = ((int)g->p->x - p->hori_x) * p->tan + (int)g->p->y;
		p->add_y *= -1;
	}
	rays_dist_hori(p, g);
}

void	check_vertical(t_pos *p, t_game *g)
{
	p->add_y = TILE_SIZE;
	p->map_p = 10;
	p->add_x = TILE_SIZE / (tan(deg_to_rad(p->rays)));
	if (sin(deg_to_rad(p->rays)) > 0.001)
	{
		p->verti_y = ((int)g->p->y / TILE_SIZE) * TILE_SIZE - 0.001;
		p->verti_x = ((int)g->p->y - p->verti_y) / p->tan + (int)g->p->x;
		p->add_y *= -1;
	}
	else if (sin(deg_to_rad(p->rays)) < -0.001)
	{
		p->verti_y = ((int)g->p->y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
		p->verti_x = ((int)g->p->y - p->verti_y) / p->tan + (int)g->p->x;
		p->add_x *= -1;
	}
	else
	{
		p->verti_x = (int)g->p->x;
		p->verti_y = (int)g->p->y;
		p->map_p = -1;
	}
	if (p->map_p >= 0)
		rays_dist_verti(p, g);
}

void	insert_rays(t_game *g)
{
	g->pos = malloc(sizeof(t_pos));
	if (!g->pos)
		return ;
	g->pos->info = NULL;
	g->pos->r = 0;
	g->pos->rays = fixang(g->p->direction + 30);
	g->pos->len_y = get_tab_size(g->m->map);
	while (g->pos->r < 60)
	{
		g->pos->dist_verti = 1000000;
		g->pos->dist_hori = 1000000;
		g->pos->tan = tan(deg_to_rad(g->pos->rays));
		check_horizontal(g->pos, g);
		check_vertical(g->pos, g);
		g->pos->info = init_rays_info(g->pos, g);
		g->pos->r += (double)(60 / (double)RES_X);
		g->pos->rays -= (double)(60 / (double)RES_X);
		if (g->pos->rays < 0)
			g->pos->rays = 359.9;
	}
}
