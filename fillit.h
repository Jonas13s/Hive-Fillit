/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 05:32:36 by joivanau          #+#    #+#             */
/*   Updated: 2021/12/13 13:26:00 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <fcntl.h>
# include "libft.h"
# include <stdio.h>

typedef struct s_coord
{
	int	r;
	int	c;
}				t_coord;

typedef struct s_pos
{
	t_coord	coord[3];
	char	value;
	int		x;
	int		y;
}				t_pos;

typedef struct s_map
{
	char	**map;
	int		value;
}				t_map;

int		error_handling(char *name);
int		ft_read_tetrim_from_map(t_pos pos[26], char *file_name);
int		ft_smallest_square(int num);
void	ft_print_map(t_map map);
t_map	*ft_fill_map(int size);
int		change_map(t_map *map, t_pos pos[26], int tetr, int tetris);
void	ft_freemap(t_map *map);

#endif
