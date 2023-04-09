/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leina <leina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:33:11 by bgrulois          #+#    #+#             */
/*   Updated: 2023/04/09 16:35:27 by leina            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	angle_to_rad(double angle)
{
	printf("angle %f == \nrad == %f\n\n", angle, angle * (M_PI / 180));
	return (angle * (M_PI / 180));
}

int	illegal_move(t_game *g, int i, int j)
{
	if ((g->p->direction >= 240 && g->p->direction < 360)
		&&(g->m->map[i + 1][j + 1] && g->m->map[i + 1][j + 1] == '0')
		&& (g->m->map[i + 1][j] && g->m->map[i + 1][j] == '1')
		&& (g->m->map[i][j + 1] && g->m->map[i][j + 1] == '1'))
		return (1);
	if ((g->p->direction >= 90 && g->p->direction < 180)
		&& (g->m->map[i - 1][j - 1] && g->m->map[i - 1][j - 1] == '0')
		&& (g->m->map[i - 1][j] && g->m->map[i - 1][j] == '1')
		&& (g->m->map[i][j - 1] && g->m->map[i][j - 1] == '1'))
		return (1);
	if ((g->p->direction >= 180 && g->p->direction < 240)
		&& (g->m->map[i - 1][j + 1] && g->m->map[i - 1][j + 1] == '0')
		&& (g->m->map[i - 1][j] && g->m->map[i - 1][j] == '1')
		&& (g->m->map[i][j + 1] && g->m->map[i][j + 1] == '1'))
		return (1);
	if ((g->p->direction >= 0 && g->p->direction < 90)
		&& (g->m->map[i + 1][j - 1] && g->m->map[i + 1][j - 1] == '0')
		&& (g->m->map[i + 1][j] && g->m->map[i + 1][j] == '1')
		&& (g->m->map[i][j - 1] && g->m->map[i][j - 1] == '1'))
		return (1);
	return (0);
}

int	player_in_wall(t_game *g, double next_x, double next_y)
{
	int	i;
	int	j;

	i = (int)next_y / TILE_SIZE;
	j = (int)next_x / TILE_SIZE;
	if (g->m->map[i][j] == '1' || illegal_move(g, i, j))
		return (1);
	return (0);
}

void	change_player_position(t_game *g, int keycode)
{
	if (keycode == 0)
	{
		g->p->x = g->p->x + cos(deg_to_rad(g->p->direction)) * SPEED;
		g->p->y = g->p->y - sin(deg_to_rad(g->p->direction)) * SPEED;
	}
	if (keycode == 1)
	{
		g->p->x = g->p->x - cos(deg_to_rad(g->p->direction)) * SPEED;
		g->p->y = g->p->y + sin(deg_to_rad(g->p->direction)) * SPEED;
	}
	if (keycode == 2)
	{
		g->p->y = g->p->y + cos(deg_to_rad(g->p->direction)) * SPEED;
		g->p->x = g->p->x + sin(deg_to_rad(g->p->direction)) * SPEED;
	}
	if (keycode == 3)
	{
		g->p->y = g->p->y - cos(deg_to_rad(g->p->direction)) * SPEED;
		g->p->x = g->p->x - sin(deg_to_rad(g->p->direction)) * SPEED;
	}
	if (player_in_wall(g, g->p->x, g->p->y))
		reverse_player_position(g, keycode);
	printf("dir : %f\n", g->p->direction);
}

void	reverse_player_position(t_game *g, int keycode)
{
	if (keycode == 0)
	{
		g->p->x = g->p->x - cos(deg_to_rad(g->p->direction)) * SPEED;
		g->p->y = g->p->y + sin(deg_to_rad(g->p->direction)) * SPEED;
	}
	if (keycode == 1)
	{
		g->p->x = g->p->x + cos(deg_to_rad(g->p->direction)) * SPEED;
		g->p->y = g->p->y - sin(deg_to_rad(g->p->direction)) * SPEED;
	}
	if (keycode == 2)
	{
		g->p->y = g->p->y - cos(deg_to_rad(g->p->direction)) * SPEED;
		g->p->x = g->p->x - sin(deg_to_rad(g->p->direction)) * SPEED;
	}
	if (keycode == 3)
	{
		g->p->y = g->p->y + cos(deg_to_rad(g->p->direction)) * SPEED;
		g->p->x = g->p->x + sin(deg_to_rad(g->p->direction)) * SPEED;
	}
}

void	change_player_direction(t_game *g, int keycode)
{
	if (keycode == 5)
	{
		if (g->p->direction > 360)
			g->p->direction = 0;
		else
			g->p->direction += 2;
	}
	if (keycode == 4)
	{
		if (g->p->direction < 0)
			g->p->direction = 360;
		else
			g->p->direction -= 2;
	}
}

void	motion_control(t_game *gs, int keycode)
{
	if (keycode == 4 || keycode == 5)
		change_player_direction(gs, keycode);
	else
		change_player_position(gs, keycode);
	//printf("posx -> %f, posy -> %f\n\n direction-> %f\n\n\n\n\n\n\n", gs->p->x, gs->p->y, gs->p->direction);
}

void	close_window(t_game *g)
{
	int	i;

	i = 0;
	if (g->pos != NULL)
	{
		free_rays_info(g->pos->info);
		printf("g->info %f\n", g->pos->info->wich_rays);
		while(i++ < 10)
			printf("wwwwwwwwwww\n");
		g->pos->info = NULL;
		free(g->pos);
		g->pos = NULL;
	}
	mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	printf("closed\n");
}

int	keyboard_ctl_on(int keycode, t_game *gs)
{
	if (keycode == ESC)
	{
		close_window(gs);
		return (-1);
	}
	if (keycode == W)
		gs->keycode_w = 1;
	if (keycode == S)
		gs->keycode_s = 1;
	if (keycode == D)
		gs->keycode_d = 1;
	if (keycode == A)
		gs->keycode_a = 1;
	if (keycode == LEFT)
		gs->keycode_l = 1;
	if (keycode == RIGHT)
		gs->keycode_r = 1;
	return (0);
}

int	keyboard_ctl_off(int keycode, t_game *gs)
{
	if (keycode == W)
		gs->keycode_w = 0;
	if (keycode == S)
		gs->keycode_s = 0;
	if (keycode == D)
		gs->keycode_d = 0;
	if (keycode == A)
		gs->keycode_a = 0;
	if (keycode == LEFT)
		gs->keycode_l = 0;
	if (keycode == RIGHT)
		gs->keycode_r = 0;
	return (0);
}

int	get_keyboard_event(t_game *g)
{
	if (g->keycode_w == 1)
		motion_control(g, 0);
	if (g->keycode_s == 1)
		motion_control(g, 1);
	if (g->keycode_d == 1)
		motion_control(g, 2);
	if (g->keycode_a == 1)
		motion_control(g, 3);
	if (g->keycode_r == 1)
		motion_control(g, 4);
	if (g->keycode_l == 1)
		motion_control(g, 5);
	render_next_frame(g);
	free_rays_info(g->pos->info);
	free (g->pos);
	g->pos = NULL;
	// render_image(g);
	return (0);
}

void	mlx_hooks(t_game *g)
{
	mlx_hook(g->win, 2, 1L<<0, keyboard_ctl_on, g);
	mlx_hook(g->win, 3, 1L<<1, keyboard_ctl_off, g);
	mlx_loop_hook(g->mlx, get_keyboard_event, g);
	return ;
}
