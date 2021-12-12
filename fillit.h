#ifndef FILLIT_H
# define FILLIT_H
# include <fcntl.h>
# include "libft.h"

typedef	struct	s_coord
{
	int	r;
	int	c;
}				t_coord;

typedef	struct	s_pos
{
	t_coord	coord[3];
	char	value;
	int		x;
	int		y;
}				t_pos;

int	error_handling(char *name);

int		ft_read_tetrim_from_map(t_pos pos[26], char *file_name);
char	**ft_read_from_file(char *file_name);
void	ft_free_map(char ***map);
void	ft_read_coord(char **map, t_pos pos[26], int n);
int		ft_smallest_square(int num);

void	ft_print_map(t_pos pos[26], char map[20][20], int n);
void	ft_fill_map(char map[20][20]);
int change_map(char map[20][20], t_pos pos[26], int tetr, int square, int tetris);

#endif
