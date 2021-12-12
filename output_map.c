#include "fillit.h"
#include <stdio.h>

void	ft_print_map(t_pos pos[26], char map[20][20], int n)
{
	int	i;
	int	j;

	i = -1;
	while (++i < n)
	{
		j = -1;
		while (++j < n)
			ft_putchar(map[i][j]);
		ft_putchar('\n');
	}	
}

void	ft_fill_map(char map[20][20])
{
	ft_memset(*map, '.', 400);
}

void	ft_tetr_to_map(char map[20][20], t_pos pos)
{
	int m;

	m = 0;
	map[pos.y][pos.x] = pos.value;
	while (m < 3)
	{
		map[pos.y + pos.coord[m].r][pos.x + pos.coord[m].c] = pos.value;
		++m;
	}
}

void ft_delete_tetr(char map[20][20], t_pos *pos)
{
	int m;

	m = 0;
	map[pos->y][pos->x] = '.';
	while (m < 3)
	{
		map[pos->y + pos->coord[m].r][pos->x + pos->coord[m].c] = '.';
		++m;
	}
	pos->x = 0;
	pos->y = 0;
}

static	int ft_check_pos(char map[20][20], t_pos *pos, int i, int j, int n)
{
	int flag;
	int m;

	m = 0;
	if (map[i][j] != '.')
		return (0);
	while (m < 3)
	{
		if ((j + pos->coord[m].c >= n || j + pos->coord[m].c < 0 \
				|| i + pos->coord[m].r >= n) || \
			map[i + pos->coord[m].r][j + pos->coord[m].c] != '.')
			return (0);
		else
			m++;
	}
	pos->x = j;
	pos->y = i;
	return (1);
}

int place_tetris(char map[20][20], t_pos *pos, int i, int j, int n)
{
	if (ft_check_pos(map, pos, i, j, n) == 1)
	{
		ft_tetr_to_map(map, *pos);
		return (1);
	}
	return (0);
}

int change_map(char map[20][20], t_pos pos[26], int tetr, int square, int tetris)
{
	int x;
	int y;

	y = 0;
	if (tetr == tetris)
		return (1);
	//printf("function call\n");
	//ft_print_map(pos, map, square);
	while (y < square)
	{
		x = 0;
		while (x < square && tetr < tetris)
		{
			if(place_tetris(map, &pos[tetr], x, y, square))
			{
				//printf("place tetris\n");
				//ft_print_map(pos, map, square);
				//printf("\n");
				if (change_map(map, pos, tetr + 1, square, tetris))
				{
					return (1);
				}
				else
				{
					//printf("delete\n");
					ft_delete_tetr(map, &pos[tetr]);
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}
