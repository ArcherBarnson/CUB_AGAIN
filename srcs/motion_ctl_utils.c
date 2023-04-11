#include "../includes/cub3d.h"

double	angle_to_rad(double angle)
{
	return (angle * (M_PI / 180));
}

int	illegal_move(t_game *g, int i, int j)
{
	if ((g->p->direction >= 300 && g->p->direction < 330)
		&& (g->m->map[i + 1][j] && g->m->map[i + 1][j] == '1')
		&& (g->m->map[i][j + 1] && g->m->map[i][j + 1] == '1'))
		return (1);
	if ((g->p->direction >= 120 && g->p->direction < 150)
		&& (g->m->map[i - 1][j] && g->m->map[i - 1][j] == '1')
		&& (g->m->map[i][j - 1] && g->m->map[i][j - 1] == '1'))
		return (1);
	if ((g->p->direction >= 210 && g->p->direction < 240)
		&& (g->m->map[i - 1][j] && g->m->map[i - 1][j] == '1')
		&& (g->m->map[i][j + 1] && g->m->map[i][j + 1] == '1'))
		return (1);
	if ((g->p->direction >= 30 && g->p->direction < 60)
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
	if (g->m->map[i][j] == '1'
		|| g->m->map[i][j] == ' '
		|| illegal_move(g, i, j))
		return (1);
	return (0);
}
