/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_assets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:17:39 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/01 10:39:08 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "libft.h"

void	handle_collectible(t_game *game, int new_row, int new_col)
{
	DRAW_IMG(game->mlx, game->prev_img, game->p_col * T_S, game->p_row * T_S);
	game->map[new_row][new_col] = '0';
	game->collectibles--;
}

void	handle_exit(t_game *game)
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
}

void	handle_player_movement(t_game *game, int new_row, int new_col)
{
	if (game->map[new_row][new_col] == 'X')
	{
		puts("Perdu !");
		mlx_close_window(game->mlx);
		free_game(game);
		mlx_terminate(game->mlx);
		exit(EXIT_FAILURE);
	}
	game->p_row = new_row;
	game->p_col = new_col;
	update_player_icon(game);
	DRAW_IMG(game->mlx, game->cur_p, new_col * T_S, new_row * T_S);
}
