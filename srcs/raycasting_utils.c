/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcorpora <lcorpora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 09:09:05 by lcorpora          #+#    #+#             */
/*   Updated: 2023/03/20 23:13:34 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

float	deg_to_rad(float	a)
{
	return ((a * M_PI) / 180.0);
}

int	fix_ang(int	a)
{
	if(a > 359)
		a -= 360;
	if(a < 0)
		a += 360;
	return (a);
}

void	smallest_dist(t_pos *p, t_rays_info *info)
{
	if (p->dist_verti > p->dist_hori)
	{
		info->pos_x = p->hori_x;
		info->pos_y = p->hori_y;
		info->dist = p->dist_hori;
		//print_line((int)g->p->x, (int)g->p->y, info->pos_x, info->pos_y, g, TEST_2);
	}
	else
	{
		info->pos_x = p->verti_x;
		info->pos_y = p->verti_y;
		info->dist = p->dist_verti;
		//print_line((int)g->p->x, (int)g->p->y, info->pos_x, info->pos_y, g, TEST);
	}
}

t_rays_info	*init_rays_info(t_pos *p)
{
	t_rays_info	*tmp;
	t_rays_info	*tmp_2;

	tmp = (t_rays_info *)malloc(sizeof(t_rays_info));
	tmp_2 = p->info;
	tmp->rays = p->rays;
	tmp->wich_rays = p->r;
	smallest_dist(p, tmp);
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

void print_line(int x0, int y0, int x1, int y1, t_game *g, int color) // TO_REMOVE
{
   (void)color;
   (void)g;
   int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
   int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1;
   int err = dx+dy, e2; /* error value e_xy */
   while(1){  /* loop */
//    if (x0 == 191)
	// printf("x0 == %d et y0 = %d\n", x0, y0);
	// if (x0 < 0 || y0 < 0)
	// 	break ;
      //my_mlx_pixel_put(g->img, x0, y0, color);
      if (x0==x1 && y0==y1)
	   break;
      e2 = 2*err;
      if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
      if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
   }
}

void print_color_map(t_game *g, int x, int y) // TO_REMOVE
{
	int i;
	int a;

	i = 0;
	while (g->m->map[i])
	{
		a = 0;
		while (g->m->map[i][a])
		{
			if (i == x && a == y)
				printf("%s%c %s",AC_GREEN, g->m->map[i][a], AC_NORMAL);
			else
				printf("%c ",g->m->map[i][a]);
			a++;
		}
		printf("\n");
		i++;
	}
}
