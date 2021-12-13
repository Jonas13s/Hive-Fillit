/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 05:25:22 by joivanau          #+#    #+#             */
/*   Updated: 2021/12/13 13:25:25 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	ft_read_coord(char **map, t_pos pos[26], int n)
{
	int	m;
	int	top_r;
	int	top_c;
	int	i;
	int	j;

	m = -2;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			if (map[i][j] == '#' && m++ == -2)
			{
				top_r = i;
				top_c = j;
			}
			else if (map[i][j] == '#' && m >= 0)
			{
				pos[n].coord[m].c = j - top_c;
				pos[n].coord[m].r = i - top_r;
			}
		}
	}
}

static void	ft_free_map(char ***map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		ft_strdel(&(*map)[i]);
		++i;
	}
}

static char	**ft_read_from_file(char *file_name)
{
	int		fd;
	int		ret;
	char	buf[BUFF_SIZE];
	char	**map;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(1);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret <= 0)
		exit(1);
	buf[ret] = '\0';
	map = ft_strsplit(buf, '\n');
	if (!map)
		exit(1);
	close(fd);
	return (map);
}

static void	pos_setup(t_pos pos[26], int num)
{
	pos[num].value = 'A' + num;
	pos[num].x = 0;
	pos[num].y = 0;
}

int	ft_read_tetrim_from_map(t_pos pos[26], char *file_name)
{
	char	**temp;
	char	**map;
	int		i;
	int		j;
	int		num;

	map = ft_read_from_file(file_name);
	temp = (char **)malloc(sizeof(char *) * 4);
	i = 0;
	j = 0;
	num = 0;
	while (map[i])
	{
		temp[j++] = map[i++];
		if (j == 4)
		{
			pos_setup(pos, num);
			ft_read_coord(temp, pos, num++);
			ft_free_map(&temp);
			j = 0;
		}
	}
	free(temp);
	free(map);
	return (num);
}
