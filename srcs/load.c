/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:53:19 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/24 15:38:54 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	load_textures(t_game *g)
{
	printf("floor color is : %i %i %i\n", g->t->f[0], g->t->f[1], g->t->f[2]);
	printf("ceiling color is : %i %i %i\n", g->t->c[0], g->t->c[1], g->t->c[2]);
	g->t->width = TEXTURE_WIDTH;
	g->t->height = TEXTURE_HEIGHT;
	g->t->no_t = mlx_xpm_file_to_image(g->mlx, g->m->no, &g->t->width, &g->t->height);
	g->t->so_t = mlx_xpm_file_to_image(g->mlx, g->m->so, &g->t->width, &g->t->height);
	g->t->ea_t = mlx_xpm_file_to_image(g->mlx, g->m->ea, &g->t->width, &g->t->height);
	g->t->we_t = mlx_xpm_file_to_image(g->mlx, g->m->we, &g->t->width, &g->t->height);
	free(g->m->no);
	free(g->m->so);
	free(g->m->ea);
	free(g->m->we);
	if (!g->t->no_t || !g->t->so_t || !g->t->ea_t || !g->t->we_t)
		return (1);
	return (0);
}
