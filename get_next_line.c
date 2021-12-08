/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:05:39 by joivanau          #+#    #+#             */
/*   Updated: 2021/12/09 00:16:04 by joivanau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_first_line(char *sbuf, char **line, int *error)
{
	ssize_t		i;
	char		*temp;
	ssize_t		strlength;

	i = 0;
	strlength = ft_strlen(sbuf);
	while (sbuf[i] != '\n' && sbuf[i] != '\0')
		i++;
	if (i > 0)
	{
		ft_strdel(line);
		*line = ft_strsub(sbuf, 0, i);
		*error = 1;
	}
	if (i + 1 <= strlength)
	{
		temp = ft_strsub(sbuf, i + 1, strlength - 1);
		ft_strdel(&sbuf);
		sbuf = temp;
		*error = 1;
	}
	if (i + 1 >= strlength)
		ft_strdel(&sbuf);
	return (sbuf);
}

static char	*read_line(const int fd, char *sbuf, int *error)
{
	ssize_t		bytes_read;
	char		*buf;

	buf = (char *) ft_calloc(BUFF_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFF_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		sbuf = ft_strupdate(sbuf, buf);
		if (sbuf == NULL)
		{
			bytes_read = -1;
			break ;
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	ft_strdel(&buf);
	if (bytes_read == -1)
		ft_strdel(&sbuf);
	*error = bytes_read;
	return (sbuf);
}

int	get_next_line(const int fd, char **line)
{
	static char	*sbuf[MAX_FD];
	int			error;

	if (line == NULL || fd < 0 || BUFF_SIZE <= 0 || fd > MAX_FD \
	|| fd == 1 || fd == 2)
		return (-1);
	*line = ft_strdup("");
	if (!sbuf[fd])
		sbuf[fd] = ft_strdup("");
	if (!sbuf[fd])
		return (-1);
	error = 0;
	if (ft_strchr(sbuf[fd], '\n'))
	{
		sbuf[fd] = get_first_line(sbuf[fd], line, &error);
		return (error);
	}
	sbuf[fd] = read_line(fd, sbuf[fd], &error);
	if (error == -1 || sbuf[fd] == NULL)
		return (-1);
	sbuf[fd] = get_first_line(sbuf[fd], line, &error);
	return (error);
}
