#include "../includes/cub3d.h"

double	angle_to_rad(double angle)
{
	return (angle * (M_PI / 180));
}

int	illegal_move(t_game *g, int i, int j)
{
	if ((g->p->direction >= 240 && g->p->direction < 360)
		&& (g->m->map[i + 1][j + 1] && g->m->map[i + 1][j + 1] == '0')
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
