/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:37:15 by mlink             #+#    #+#             */
/*   Updated: 2022/11/15 10:38:53 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** allocates memory for each row
** saves given integer values describing if a spot is 
** empty/reserved by opponent/my_player
** 0 - empty, -1 - opponent, -2 - my_player
*/

/*
**	print map in filler.log:
**	fd_printf((*data)->fd_log, "%3d", (*data)->map[height][x - 4]);
// at the end of while loop
**	fd_printf((*data)->fd_log, "\n"); // after while loop
*/

static int	map_line(t_data **data, char *line, int height)
{
	int	x;

	x = 4;
	(*data)->map[height] = (int *)malloc(sizeof(int) * (*data)->map_width);
	if (!(*data)->map[height])
		return (0);
	while (x - 4 < (*data)->map_width)
	{
		if (line[x] == '.')
			(*data)->map[height][x - 4] = 0;
		else if (line[x] == (*data)->opponent_id || line[x] == \
		(*data)->opponent_id + 32)
			(*data)->map[height][x - 4] = -1;
		else if (line[x] == (*data)->player_id || line[x] == \
		(*data)->player_id + 32)
			(*data)->map[height][x - 4] = -2;
		x++;
	}
	return (1);
}

/*
** reads and saves line by line
** the number of rows is determined by the size of the map_height
*/

static int	save_line(t_data **data)
{
	int		height;
	char	*line;

	height = -1;
	while (++height < (*data)->map_height && get_next_line((*data)->fd, &line))
	{
		if (!map_line(data, line, height))
			return (0);
		ft_strdel(&line);
	}
	if (height == (*data)->map_height)
		return (1);
	return (0);
}

/*
** gets size for map and allocates memory for it
** creates an integer map based of map read from stdin
*/

/*
** print size for map in filler.log:
** fd_printf((*data)->fd_log, "Plateau %d %d\n", (*data)->map_height, \
(*data)->map_width); // after get_size();
*/

int	read_map(t_data **data)
{
	char	*line;

	line = NULL;
	while (get_next_line((*data)->fd, &line) > 0 && \
	ft_strncmp(line, "Plateau", 6) != 0)
		ft_strdel(&line);
	if (!line)
		return (0);
	get_size(&line, &(*data)->map_height, &(*data)->map_width);
	if (get_next_line((*data)->fd, &line) > 0)
		ft_strdel(&line);
	(*data)->map = (int **)malloc(sizeof(int *) * (*data)->map_height);
	if (!(*data)->map)
		return (0);
	if (save_line(data))
		return (1);
	return (0);
}

/*
** gets size for piece and allocates memory for it
** reads and saves data with piece to struct
** trims collums and rows without piese 
*/

/*
** print size for piece in filler.log:
** fd_printf((*data)->fd_log, "Piece %d %d\n", (*data)->piece_height,\
(*data)->piece_width); // after get_size();
** print piece in filler.log:
** fd_printf((*data)->fd_log, "%s\n", (*data)->piece[height]);\
// before ft_strdel();
*/

int	read_piece(t_data **data)
{
	int		height;
	char	*line;

	line = NULL;
	while (get_next_line((*data)->fd, &line) > 0 && \
	ft_strncmp(line, "Piece", 4) != 0)
		ft_strdel(&line);
	if (!line)
		return (0);
	get_size(&line, &(*data)->piece_height, &(*data)->piece_width);
	(*data)->piece = (char **)malloc(sizeof(char *) * ((*data)->piece_height));
	height = -1;
	while (++height < (*data)->piece_height && \
	get_next_line((*data)->fd, &line))
	{
		(*data)->piece[height] = ft_strdup((const char *)(line));
		ft_strdel(&line);
	}
	if (height == (*data)->piece_height)
		return (trim_piece(data));
	return (0);
}
