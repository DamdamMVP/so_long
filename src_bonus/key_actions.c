/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 03:27:21 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/03 21:16:29 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "libft.h"

static void	check_direction(mlx_key_data_t keydata, t_game *game,
	int *new_row, int *new_col)
{
	if (keydata.key == MLX_KEY_W
		&& game->map[game->p_row - 1][game->p_col] != '1')
		(*new_row)--;
	else if (keydata.key == MLX_KEY_S
		&& game->map[game->p_row + 1][game->p_col] != '1')
		(*new_row)++;
	else if (keydata.key == MLX_KEY_A
		&& game->map[game->p_row][game->p_col - 1] != '1')
		(*new_col)--;
	else if (keydata.key == MLX_KEY_D
		&& game->map[game->p_row][game->p_col + 1] != '1')
		(*new_col)++;
}

static void	handle_escape_key(t_game *game)
{
	mlx_close_window(game->mlx);
	free_game(game);
	mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}

static void	handle_move(t_game *game, int new_row, int new_col)
{
	char	*move_count_str;

	move_count_str = ft_itoa(game->move_count);
	update_prev_image(game, new_row, new_col);
	handle_player_movement(game, new_row, new_col);
	game->move_count++;
	free(move_count_str);
	ft_printf("Nombre de déplacements : %d\n", game->move_count);
}

void	move_player(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		new_row;
	int		new_col;

	game = (t_game *)param;
	new_row = game->p_row;
	new_col = game->p_col;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			handle_escape_key(game);
		else
		{
			check_direction(keydata, game, &new_row, &new_col);
			if (new_row != game->p_row || new_col != game->p_col)
				handle_move(game, new_row, new_col);
		}
	}
}
