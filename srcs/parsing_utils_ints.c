/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgrulois <bgrulois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:54:24 by bgrulois          #+#    #+#             */
/*   Updated: 2023/03/31 14:12:43 by bgrulois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_n_lines(int fd)
{
	int		n;
	char	*dud;

	n = 1;
	dud = NULL;
	if (fd < 0)
		return (n);
	dud = get_next_line(fd);
	while (dud != NULL)
	{
		free(dud);
		dud = get_next_line(fd);
		n++;
	}
	free(dud);
	return (n);
}

int	is_a_valid_tile(char tile)
{
	if (tile == '1' || tile == '0' || tile == ' ')
		return (1);
	if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
		return (2);
	return (0);
}

int	is_a_dir(char *filename)
{
	if (open(filename, O_DIRECTORY) > 0)
	{
		write(2, IS_A_DIR, 44);
		return (1);
	}
	return (0);
}
