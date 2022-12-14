/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlink <mlink@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:37:00 by mlink             #+#    #+#             */
/*   Updated: 2022/11/08 11:18:32 by mlink            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/filler.h"

/*
** finds player information
*/

/*
** filler.log:
** fd_printf((*data)->fd_log, "My = '%c'\n", (*data)->player_id); 
/ before ft_strdel() and return(1)
** if "-p1 ./mlink.filler" my id will be 'O' else 'X' 
*/

int	get_player(t_data **data)
{
	char	*line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (!(ft_strncmp(line, "$$$ exec p", 9)) && ft_strstr(line, "mlink"))
		{
			if (line[10] == '1')
			{
				(*data)->player_id = 'O';
				(*data)->opponent_id = 'X';
			}
			else
			{
				(*data)->player_id = 'X';
				(*data)->opponent_id = 'O';
			}
			ft_strdel(&line);
			return (1);
		}
		ft_strdel(&line);
	}
	return (0);
}

/*
** saves sizes and frees the line
*/

void	get_size(char **line, int *height, int *widht)
{
	int	start;

	if (ft_strncmp("Piece", *line, 5) == 0)
		start = 6;
	else
		start = 8;
	*height = ft_atoi(&(*line)[start]);
	*widht = ft_atoi((*line) + start + ft_intlen(*height) + 1);
	ft_strdel(&(*line));
}
