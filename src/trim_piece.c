#include "../includes/filler.h"

// /*
// ** checks how many horizontal lines of old piece are not empty.
// */

static void	get_new_height(t_data **data, int start_y)
{
	int	new_height;

	new_height = 0;
	while (start_y < (*data)->piece_height)
	{
		if (ft_strchr((*data)->piece[start_y], '*') != NULL)
			new_height++;
		start_y++;
	}
	(*data)->real_height = new_height;
}

// /*
// ** checks how many vertical lines of old piece are not empty.
// */

static void	get_new_width(t_data **data, int start_x, int start_y)
{
	int	new_width;
	int	x_counter;

	new_width = 0;
	while (++start_y < (*data)->piece_height)
	{
        if (ft_strchr((*data)->piece[start_y], '*') != NULL)
        {
            x_counter = start_x;
		    while ((*data)->piece[start_y][x_counter] != '*')
                x_counter++;
            while ((*data)->piece[start_y][x_counter] == '*')
                x_counter++;
            if (x_counter - start_x > new_width)
                new_width = x_counter - start_x;
        }
	}
    (*data)->real_width = new_width;
}

// /*
// ** finds the upper left coordinates of where piece starts.
// */

static int	find_start(t_data **data)
{
	int	y_index;
	int	x_index;

	y_index = -1;
	while (++y_index < (*data)->piece_height)
	{
		x_index = -1;
		while (++x_index < (*data)->piece_width)
		{
			if ((*data)->piece[y_index][x_index] == '*')
			{
				if (x_index < (*data)->start_width)
                    (*data)->start_width = x_index;
                if (y_index < (*data)->start_height)
                    (*data)->start_height = y_index;
			}
		}
	}
	return (1);
}


// // /*
// // ** copies piece without free lines and columns
// // */

static int save_new_piece(t_data **data, int start_y)
{
    int y_index;
    char    **new_piece;

    new_piece = NULL;
    new_piece = (char**)malloc(sizeof(char*) * (*data)->real_height);
    if (!new_piece)
        return (0);
    y_index = 0;
    while (y_index < (*data)->real_height)
    {
        new_piece[y_index] = ft_strndup((const char*)(*data)->piece[start_y] \
        + (*data)->start_width, (*data)->real_width);
        fd_printf((*data)->fd_log, "%s\n", new_piece[y_index]);
        y_index++;
        start_y++;
    }
    // 	free_piece(data);
	(*data)->piece = new_piece;
    return (1);
}

// // /*
// // ** trims out unnecessary empty lines from piece
// // */

int		trim_piece(t_data **data)
{
    (*data)->start_height = (*data)->piece_height;
    (*data)->start_width = (*data)->piece_width;
    find_start(data);
    get_new_height(data, (*data)->start_height);
    get_new_width(data, (*data)->start_width, (*data)->start_height - 1);
    fd_printf((*data)->fd_log, "New Piece %d %d\n", (*data)->real_height, (*data)->real_width);
	return (save_new_piece(data, (*data)->start_height));
}