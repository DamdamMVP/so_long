/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:21:24 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/03 21:17:01 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "libft.h"

void	draw_tile(t_game *game, char tile, int col, int row)
{
	if (tile == '1')
		DRAW_IMG(game->mlx, game->assets.wall[0], col * T_S, row * T_S);
	else if (tile == '0' || tile == 'X')
		DRAW_IMG(game->mlx, game->assets.c_inv, col * T_S, row * T_S);
	else if (tile == 'P')
	{
		update_player_icon(game);
		DRAW_IMG(game->mlx, game->cur_p, col * T_S, row * T_S);
	}
	else if (tile == 'C')
		DRAW_IMG(game->mlx, game->assets.c_col, col * T_S, row * T_S);
	else if (tile == 'E')
		DRAW_IMG(game->mlx, game->assets.exit, col * T_S, row * T_S);
}

void	draw_map(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			draw_tile(game, game->map[row][col], col, row);
			col++;
		}
		row++;
	}
}
