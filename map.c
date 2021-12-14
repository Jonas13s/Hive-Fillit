/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 05:20:37 by joivanau          #+#    #+#             */
/*   Updated: 2021/12/14 15:59:44 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_map	*ft_fill_map(int size)
{
	t_map	*map;
	int		x;

	map = (t_map *)malloc(sizeof(t_map));
	map->map = (char **)malloc(sizeof(char *) * size);
	map->value = size;
	if (!map->map)
		return (NULL);
	x = 0;
	while (x < size)
	{
		map->map[x] = ft_strnew(size);
		ft_memset(map->map[x], '.', size);
		x++;
	}
	return (map);
}

void	ft_freemap(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->value)
	{
		ft_strdel(&map->map[i]);
		i++;
	}
	free(map->map);
	free(map);
}

void	ft_print_map(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map.value)
	{
		j = 0;
		while (j < map.value)
		{
			ft_putchar(map.map[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

int	ft_smallest_square(int num)
{
	int	count;
	int	i;

	count = num * 4;
	i = 2;
	while (count > i * i)
		++i;
	return (i);
}
