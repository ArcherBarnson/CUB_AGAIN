/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motion_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:33:11 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/22 19:30:29 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
}

void	mlx_hooks(t_game *g)
{
	mlx_hook(g->win, 2, 1L << 0, keyboard_ctl_on, g);
	mlx_hook(g->win, 3, 1L << 1, keyboard_ctl_off, g);
	mlx_hook(g->win, 33, 1L << 17, (void *)exit_game, g);
	mlx_loop_hook(g->mlx, get_keyboard_event, g);
	return ;
}
