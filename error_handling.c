/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:36:11 by joivanau          #+#    #+#             */
/*   Updated: 2021/12/08 17:26:27 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int	symbol_check(char *str, int *row, int *blockcount)
{
	size_t	i;

	i = 0;
	if (*row == 4)
	{
		if (*blockcount != 4)
		{
			*blockcount = 0;
			*row = 0;
			return (-1);
		}
		*blockcount = 0;
		*row = 0;
		if (ft_strlen(str) != 0)
			return (-1);
		return (1);
	}
	++*row;
	while (str[i] == '#' || str[i] == '.' || i < 4)
	{
		if (str[i] == '#')
			++*blockcount;
		if (str[i + 1] == '\0' && i == 3)
			return (1);
		++i;
	}
	return (-1);
}

int	touching_block(char **str)
{
	int	x;
	int	y;
	int	connecting;

	y = 0;
	connecting = 0;
	while (y <= 3)
	{
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
		y++;
	}
	if (connecting == 3 || connecting == 4)
		return (1);
	return (-1);
}

void	delete_data(char **line)
{
	int	i;

	i = 0;
	while (i <= 4)
	{
		ft_strdel(&line[i]);
		i++;
	}
}

int error_check(char *name)
{
	char	*line;
	int		fd;
	int		errorresult;
	int		row;
	int		blockcount;
	char	*lastblock[5];

	blockcount = 0;
	row = 0;
	fd = open(name, O_RDONLY);
	errorresult = 1;
	while (1)
	{
		ft_strdel(&line);
		if (get_next_line(fd, &line) <= 0)
			break ;
		if (errorresult == 1)
		{
			lastblock[row] = ft_strdup(line);
			if (symbol_check(line, &row, &blockcount) == -1)
				errorresult = -1;
			if (row == 4)
			{
				if (touching_block(lastblock) == -1)
					errorresult = -1;
				delete_data(lastblock);
			}
		}
	}
	ft_strdel(&line);
	delete_data(lastblock);
	if (row != 4 && errorresult == 1)
		errorresult = -1;
	return (errorresult);
}



int main(void)
{
	printf("%d\n", error_check("mapcorrect"));
	return (0);
}