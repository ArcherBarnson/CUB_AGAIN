#include "../includes/cub3d.h"

void	draw_scene(t_game *g)
{

	int	x = 0;
	int	y = 0;

	g->img->img = mlx_new_image(g->mlx, RES_X, RES_Y);
	g->img->addr = mlx_get_data_addr(g->img->img, &g->img->bits_per_pixel, &g->img->line_length, &g->img->endian);
	while (y < TILE_SIZE)
	{
		while (x < TILE_SIZE)
		{
			//color = g->t->no_t.addr[x * 4 + 4 * g->t->no_t.line_length * y];
			g->img->addr[y * 4 * g->img->line_length / 4 + x * 4] = g->t->no_t.addr[y * 4 * g->t->no_t.line_length / 4 + x * 4];
			//my_mlx_pixel_put(g->img, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	//my_mlx_pixel_put(g->img, (int)g->p->x, (int)g->p->y, GREEN);
	//insert_rays(g);
	mlx_put_image_to_window(g->mlx, g->win, g->img->img, 0, 0);
}

int	main(int ac, char **av)
{
	t_game	*g;
	//int	dbg_return;

	g = init_and_parse(ac, av[1]);
	if (!g)
		return (1);
	g->win = mlx_new_window(g->mlx, RES_X, RES_Y, "curs3d");
	//g->t->no_t.img = mlx_xpm_file_to_image(g->mlx, g->m->no, &a, &b);
	//if (a != TEXTURE_WIDTH || b != TEXTURE_HEIGHT || !g->t->no_t.img)
	//	return (1);		
	g->t->no_t.addr = mlx_get_data_addr(g->t->no_t.img, &g->t->no_t.bits_per_pixel, &g->t->no_t.line_length, &g->t->no_t.endian);
	draw_scene(g);
	//mlx_hooks(g);
	mlx_loop(g->mlx);
	//dbg_return = ft_parsing(g, av[1]);
	//printf("return value : %i\n", dbg_return);
	return (0);
}
