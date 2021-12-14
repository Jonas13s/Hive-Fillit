/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:36:11 by joivanau          #+#    #+#             */
/*   Updated: 2021/12/14 15:54:16 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
/*
Read line by line;
check everyline if it has = 4bytes, and if the charachters are either '.' || '#';
check if fifth line is newline, and also how many # are there, it has to be 4;

*/

static int	delete_data(char **line, int size)
{
	while (size-- > 0)
		ft_strdel(&line[size]);
	return (-1);
}

static int	touching_block(char **str, int y)
{
	int	x;
	int	connecting;

	connecting = 0;
	x = 0;
	while (x <= 3)
	{
		if (str[y][x] == '#')
		{
			if (x < 3)
				if (str[y][x + 1] == '#')
					connecting++;
			if (y < 3)
				if (str[y + 1][x] == '#')
					connecting++;
		}
		x++;
	}
	return (connecting);
}

static int	check_symbol(char **str)
{
	int	i;
	int	y;
	int	blocksize;
	int	connectedblocks;

	connectedblocks = 0;
	blocksize = 0;
	y = -1;
	while (y++ < 3)
	{
		i = -1;
		while (str[y][++i] == '#' || str[y][i] == '.')
			if (str[y][i] == '#')
				blocksize ++;
		if (str[y][i] != '\0' || i != 4)
			return (-1);
		connectedblocks += touching_block(str, y);
	}
	if (blocksize != 4 || (connectedblocks != 3 && connectedblocks != 4))
		return (-1);
	return (1);
}

static int	error_check(int fd, int tetcount, int *error)
{
	char	*block[5];
	int		y;

	y = 0;
	while (get_next_line(fd, &block[y]) > 0)
	{
		if (y == 4)
		{
			if (ft_strlen(block[y]) != 0)
				*error = -1;
			delete_data(block, 5);
			y = -1;
		}
		if (y == 3)
		{
			if (check_symbol(block) != 1)
				*error = -1;
			tetcount++;
		}
		y++;
	}
	if (y != 4 || tetcount > 26)
		*error = -1;
	delete_data(block, y);
	return (1);
}

int	error_handling(char *name)
{
	int	fd;
	int	tetcount;
	int	error;

	error = 1;
	tetcount = 0;
	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		write(1, "error\n", 6);
		return (-1);
	}
	error_check(fd, tetcount, &error);
	if (error == -1)
		write(1, "error\n", 6);
	close(fd);
	return (error);
}
