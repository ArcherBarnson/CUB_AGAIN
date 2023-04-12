/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_ctl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:24:53 by bgrulois          #+#    #+#             */
/*   Updated: 2023/04/12 16:24:56 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	return (0);
}
