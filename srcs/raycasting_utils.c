/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leina <leina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:09:05 by lcorpora          #+#    #+#             */
/*   Updated: 2023/04/11 13:02:00 by leina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	deg_to_rad(float a)
{
	return ((a * M_PI) / 180.0);
}

float	fixang(float a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

void	smallest_dist(t_pos *p, t_rays_info *info, t_game *g)
{
	float	r;

	r = fixang(g->p->direction - p->rays);
	if (p->dist_verti > p->dist_hori)
	{
		info->pos_x = p->hori_x;
		info->pos_y = p->hori_y;
		if (p->rays < 270 && p->rays > 90)
			info->side = 3;
		else
			info->side = 2;
		info->dist = roundf(p->dist_hori * cos(deg_to_rad(r)));
	}
	else
	{
		info->pos_x = p->verti_x;
		info->pos_y = p->verti_y;
		if (p->rays < 180 && p->rays > 0)
			info->side = 0;
		else
			info->side = 1;
		info->dist = roundf(p->dist_verti * cos(deg_to_rad(r)));
	}
}

t_rays_info	*init_rays_info(t_pos *p, t_game *g)
{
	t_rays_info	*tmp;
	t_rays_info	*tmp_2;

	tmp = (t_rays_info *)malloc(sizeof(t_rays_info));
	tmp_2 = p->info;
	tmp->rays = p->rays;
	tmp->wich_rays = p->r;
	smallest_dist(p, tmp, g);
	tmp->next = NULL;
	if (tmp_2 == NULL)
	{
		tmp->prev = NULL;
		p->info = tmp;
	}
	else
	{
		while (tmp_2->next != NULL)
			tmp_2 = tmp_2->next;
		tmp->prev = tmp_2;
		tmp_2->next = tmp;
	}
	return (p->info);
}

void	free_rays_info(t_rays_info *info)
{
	t_rays_info	*tmp;
	t_rays_info	*tmp_2;

	tmp = info;
	while (tmp->prev != NULL)
		tmp = tmp->prev;
	while (tmp != NULL)
	{
		tmp_2 = tmp->next;
		free(tmp);
		tmp = tmp_2;
	}
	tmp = NULL;
	free(tmp);
}
