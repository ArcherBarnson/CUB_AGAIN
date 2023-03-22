/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leina <leina@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:55:05 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/22 18:10:19 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_game *init_and_parse(int ac, char *map_file)
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
		return (NULL);
	g->mlx = mlx_init();
	if (!g->mlx)
		return (NULL);
	if (load_textures(g) != 0)
	{
		write(2, T_LOAD_ERROR, 44);
		return (NULL);
	}
	init_player_data(g);
	return (g);
}

int	main(int ac, char **av)
{
	t_game	*g;
	//int	dbg_return;

	g = init_and_parse(ac, av[1]);
	if (!g)
		return (1);
	g->win = mlx_new_window(g->mlx, RES_X, RES_Y, "curs3d");
	mlx_hooks(g);
	mlx_loop(g->mlx);
	//dbg_return = ft_parsing(g, av[1]);
	//printf("return value : %i\n", dbg_return);
	return (0);
}
