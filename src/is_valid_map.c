/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 22:27:43 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/07 05:40:58 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

int	is_valid_map(char **map)
{
	int	row;

	row = 0;
	if (!is_valid_char(map))
		return (0);
	if (!have_require_elem(map))
		return (0);
	if (!is_map_close(map))
		return (0);
	if (!can_be_finish(map))
		return (0);
	return (1);
}

int	is_valid_char(char **map)
{
	int		row;
	int		i;
	char	*valid_chars;

	valid_chars = "01CEP";
	row = 0;
	while (map[row])
	{
		i = 0;
		while (map[row][i])
		{
			if (!ft_strchr(valid_chars, map[row][i]))
			{
				return (ft_error("Error\n"), 0);
			}
			i++;
		}
		row++;
	}
	return (1);
}

int	is_map_close(char **map)
{
	int	row;
	int	col;
	int	strlen;

	strlen = ft_strlen(map[0]);
	col = -1;
	if (map[1] == NULL)
	{
		while (map[0][++col])
			if (map[0][col] != '1')
				return (ft_error("Error\n"), 0);
		return (1);
	}
	while (map[0][++col])
		if (map[0][col] != '1')
			return (ft_error("Error\n"), 0);
	row = 0;
	while (map[++row + 1])
		if (map[row][0] != '1' || map[row][strlen - 1] != '1')
			return (ft_error("Error\n"), 0);
	col = -1;
	while (map[row][++col])
		if (map[row][col] != '1')
			return (ft_error("Error\n"), 0);
	return (1);
}

int	have_require_elem(char **map)
{
	int			row;
	int			i;
	t_elements	pec;

	ft_memset(&pec, 0, sizeof(t_elements));
	row = 0;
	while (map[row])
	{
		i = 0;
		while (map[row][i])
		{
			if (map[row][i] == 'P')
				pec.p++;
			if (map[row][i] == 'E')
				pec.e++;
			if (map[row][i] == 'C')
				pec.c++;
			i++;
		}
		row++;
	}
	if (pec.p != 1 || pec.e != 1 || pec.c < 1)
		return (ft_error("Error\n"), 0);
	return (1);
}
