#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}


int	eval_t_y(int y, int ws, double ratio)
{
	double	t_y;

	t_y = (double)(y - ws) / ratio;
	return ((int)t_y);
}

void	eval_t_color(t_game *g, t_slice *slice, int y, double ratio)
{
	t_data	*tx;
	int		i;

	tx = eval_tx_img(g, slice);
	i = 0;
	while (i < 4)
	{
		g->img->addr[y * g->img->line_length
			+ slice->pos_x * 4 + i]
			= tx->addr[eval_t_y(y, slice->wall_start, ratio)
			* g->t->so_t.line_length
			+ (int)(slice->wall_pos) * 4 + i];
		i++;
	}
}

t_data	*eval_tx_img(t_game *g, t_slice *slice)
{
	if (slice->side == 0)
		return (&g->t->no_t);
	if (slice->side == 1)
		return (&g->t->so_t);
	if (slice->side == 2)
		return (&g->t->ea_t);
	if (slice->side == 3)
		return (&g->t->we_t);
	return (NULL);
}
