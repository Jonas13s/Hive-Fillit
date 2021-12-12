#include "fillit.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_pos 	pos[26];
	char	map[20][20];
	int		num;
	int		square;

	if (error_handling(argv[1]) == -1)
	{
		printf("error\n");
		return (-1);
	}
	num = ft_read_tetrim_from_map(pos, argv[1]);
	ft_fill_map(map);
	square = ft_smallest_square(num);
	
	//printf("%d %d %d\n" , pos[2].coord[0].r, pos[2].coord[1].r, pos[2].coord[2].r);
	//printf("%d %d %d\n" , pos[2].coord[0].c, pos[2].coord[1].c, pos[2].coord[2].c);
	while(!change_map(map, pos, 0, square, num))
	{
		square++;
	}
	ft_print_map(pos, map, square);
	return (0);
}