/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_be_finish.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 23:31:21 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/03 19:57:59 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

static int	find_start_position(char **map_copy, int *p_row, int *p_col)
{
	int	row;
	int	col;

	*p_row = -1;
	*p_col = -1;
	row = 0;
	while (map_copy[row])
	{
		col = 0;
		while (map_copy[row][col] && map_copy[row][col] != 'P')
			col++;
		if (map_copy[row][col] == 'P')
		{
			*p_row = row;
			*p_col = col;
			break ;
		}
		row++;
	}
	return (*p_row != -1 && *p_col != -1);
}

static int	verify_map_finishable(char **map_copy)
{
	int	row;
	int	col;

	row = 0;
	while (map_copy[row])
	{
		col = 0;
		while (map_copy[row][col])
		{
			if (map_copy[row][col] == 'C' || map_copy[row][col] == 'E')
			{
				free_map(map_copy);
				return (ft_error("Error\n"), 0);
			}
			col++;
		}
		row++;
	}
	return (1);
}

int	can_be_finish(char **map)
{
	char	**map_copy;
	int		p_row;
	int		p_col;

	map_copy = copy_map(map);
	if (!map_copy)
		return (ft_error("Error\n"), 0);
	if (!find_start_position(map_copy, &p_row, &p_col))
	{
		free_map(map_copy);
		return (ft_error("Error\n"), 0);
	}
	flood_fill(map_copy, p_row, p_col);
	if (!verify_map_finishable(map_copy))
		return (0);
	free_map(map_copy);
	return (1);
}

void	flood_fill(char **map, int row, int col)
{
	if (map[row][col] == '1' || map[row][col] == 'V')
		return ;
	map[row][col] = 'V';
	flood_fill(map, row - 1, col);
	flood_fill(map, row + 1, col);
	flood_fill(map, row, col - 1);
	flood_fill(map, row, col + 1);
}
