/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_assets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:17:39 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/01 09:52:12 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

static void	handle_collectible(t_game *game, int new_row, int new_col)
{
	DRAW_IMG(game->mlx, game->prev_img, game->p_col * T_S, game->p_row * T_S);
	game->prev_img = game->assets.c_0;
	game->map[new_row][new_col] = '0';
	game->collectibles--;
}

static void	handle_exit(t_game *game)
{
	if (game->collectibles == 0)
	{
		game->move_count++;
		ft_printf("Nombre de déplacements : %d\n", game->move_count);
		puts("You win!");
		mlx_close_window(game->mlx);
		free_game(game);
		mlx_terminate(game->mlx);
		exit(EXIT_SUCCESS);
	}
	else
	{
		DRAW_IMG(game->mlx, game->prev_img, game->p_col * T_S,
			game->p_row * T_S);
		game->prev_img = game->assets.exit;
	}
}

static void	handle_default(t_game *game)
{
	DRAW_IMG(game->mlx, game->prev_img, game->p_col * T_S, game->p_row * T_S);
	game->prev_img = game->assets.c_0;
}

void	handle_player_movement(t_game *game, int new_row, int new_col)
{
	game->p_row = new_row;
	game->p_col = new_col;
	DRAW_IMG(game->mlx, game->assets.player, new_col * T_S, new_row * T_S);
}

void	update_prev_image(t_game *game, int new_row, int new_col)
{
	if (game->map[new_row][new_col] == 'C')
		handle_collectible(game, new_row, new_col);
	else if (game->map[new_row][new_col] == 'E')
		handle_exit(game);
	else
		handle_default(game);
}
