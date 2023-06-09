/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leina <leina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:55:05 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/29 22:55:34 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	render_next_frame(t_game *g)
{
	render_image(g);
	mlx_destroy_image(g->mlx, g->img->img);
	g->img->img = NULL;
	return (1);
}

void	close_window(t_game *g)
{
	exit_game(g);
}

t_game	*init_and_parse(int ac, char *map_file)
{
	t_game	*g;

	g = NULL;
	if (ac != 2)
	{
		write(2, NO_ARG, 43);
		return (NULL);
	}
	g = init();
	if (!g)
		return (NULL);
	if (ft_parsing(g, map_file) != 0)
		return (init_failure(g));
	g->mlx = mlx_init();
	if (!g->mlx)
		return (init_failure(g));
	if (load_textures(g) != 0)
	{
		write(2, T_LOAD_ERROR, 44);
		return (init_failure(g));
	}
	init_player_data(g);
	return (g);
}

int	main(int ac, char **av)
{
	t_game	*g;

	g = init_and_parse(ac, av[1]);
	if (!g)
		return (1);
	g->win = mlx_new_window(g->mlx, RES_X, RES_Y, "curs3d");
	mlx_hooks(g);
	mlx_loop(g->mlx);
	return (0);
}
