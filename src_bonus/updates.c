/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 07:34:53 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/01 10:42:43 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "libft.h"

void	update_player_icon(t_game *game)
{
	int	row;
	int	col;
	int	bomb_count;

	row = game->p_row;
	col = game->p_col;
	bomb_count = 0;
	if (game->map[row - 1][col - 1] == 'X')
		bomb_count++;
	if (game->map[row - 1][col] == 'X')
		bomb_count++;
	if (game->map[row - 1][col + 1] == 'X')
		bomb_count++;
	if (game->map[row][col - 1] == 'X')
		bomb_count++;
	if (game->map[row][col + 1] == 'X')
		bomb_count++;
	if (game->map[row + 1][col - 1] == 'X')
		bomb_count++;
	if (game->map[row + 1][col] == 'X')
		bomb_count++;
	if (game->map[row + 1][col + 1] == 'X')
		bomb_count++;
	if (bomb_count >= 0 && bomb_count <= 7)
		game->cur_p = game->assets.p[bomb_count];
}

void	update_case_icon(t_game *game, int row, int col)
{
	int	bomb_count;

	bomb_count = 0;
	if (game->map[row - 1][col - 1] == 'X')
		bomb_count++;
	if (game->map[row - 1][col] == 'X')
		bomb_count++;
	if (game->map[row - 1][col + 1] == 'X')
		bomb_count++;
	if (game->map[row][col - 1] == 'X')
		bomb_count++;
	if (game->map[row][col + 1] == 'X')
		bomb_count++;
	if (game->map[row + 1][col - 1] == 'X')
		bomb_count++;
	if (game->map[row + 1][col] == 'X')
		bomb_count++;
	if (game->map[row + 1][col + 1] == 'X')
		bomb_count++;
	if (bomb_count >= 0 && bomb_count <= 7)
		game->prev_img = game->assets.c[bomb_count];
	if (game->map[row][col] == 'E')
		game->prev_img = game->assets.exit;
}

void	update_prev_image(t_game *game, int new_row, int new_col)
{
	update_case_icon(game, game->p_row, game->p_col);
	DRAW_IMG(game->mlx, game->prev_img, game->p_col * T_S, game->p_row * T_S);
	if (game->map[new_row][new_col] == 'C')
		handle_collectible(game, new_row, new_col);
	else if (game->map[new_row][new_col] == 'E')
		handle_exit(game);
}
