/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 05:24:30 by joivanau          #+#    #+#             */
/*   Updated: 2021/12/13 12:44:44 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	ft_tetr_to_map(t_map *map, t_pos pos)
{
	int	m;

	m = 0;
	map->map[pos.y][pos.x] = pos.value;
	while (m < 3)
	{
		map->map[pos.y + pos.coord[m].r][pos.x + pos.coord[m].c] = pos.value;
		++m;
	}
}

void	ft_delete_tetr(t_map *map, t_pos *pos)
{
	int	m;

	m = 0;
	map->map[pos->y][pos->x] = '.';
	while (m < 3)
	{
		map->map[pos->y + pos->coord[m].r][pos->x + pos->coord[m].c] = '.';
		++m;
	}
	pos->x = 0;
	pos->y = 0;
}

static	int	ft_check_pos(t_map map, t_pos *pos, int i, int j)
{
	int	flag;
	int	m;

	m = 0;
	if (map.map[i][j] != '.')
		return (0);
	while (m < 3)
	{
		if ((j + pos->coord[m].c >= map.value || j + pos->coord[m].c < 0 \
				|| i + pos->coord[m].r >= map.value) || \
			map.map[i + pos->coord[m].r][j + pos->coord[m].c] != '.')
			return (0);
		else
			m++;
	}
	pos->x = j;
	pos->y = i;
	return (1);
}

int	place_tetris(t_map *map, t_pos *pos, int i, int j)
{
	if (ft_check_pos(*map, pos, i, j) == 1)
	{
		ft_tetr_to_map(map, *pos);
		return (1);
	}
	return (0);
}

int	change_map(t_map *map, t_pos pos[26], int tetr, int tetris)
{
	int	x;
	int	y;

	y = 0;
	if (tetr == tetris)
		return (1);
	while (y < map->value)
	{
		x = 0;
		while (x < map->value && tetr < tetris)
		{
			if (place_tetris(map, &pos[tetr], x, y))
			{
				if (change_map(map, pos, tetr + 1, tetris))
					return (1);
				else
					ft_delete_tetr(map, &pos[tetr]);
			}
			x++;
		}
		y++;
	}
	return (0);
}
