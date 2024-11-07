/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:02:47 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/07 05:46:20 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include "libft.h"

void	find_player_position(t_game *game)
{
	game->p_row = 0;
	while (game->map[game->p_row])
	{
		game->p_col = 0;
		while (game->map[game->p_row][game->p_col])
		{
			if (game->map[game->p_row][game->p_col] == 'P')
			{
				game->prev_img = game->assets.c[0];
				return ;
			}
			game->p_col++;
		}
		game->p_row++;
	}
}

void	free_game(t_game *game)
{
	int	i;

	if (game)
	{
		i = 0;
		while (i < 8)
		{
			if (game->assets.p[i])
				mlx_delete_image(game->mlx, game->assets.p[i]);
			i++;
		}
		i = 0;
		while (i < 12)
		{
			if (game->assets.c[i])
				mlx_delete_image(game->mlx, game->assets.c[i]);
			i++;
		}
		free_map(game->map);
	}
}

int32_t	main(int argc, char **argv)
{
	t_game	game;
	char	*fd_name;

	if (argc != 2)
		return (ft_error("Error\n"), EXIT_FAILURE);
	fd_name = argv[1];
	game.map = read_map(fd_name);
	if (!game.map)
		return (free_map(game.map), EXIT_FAILURE);
	if (!is_valid_map(game.map))
		return (free_map(game.map), EXIT_FAILURE);
	initialize_window_size(&game);
	game.mlx = mlx_init(game.win_width, game.win_height, "MLX42", false);
	if (!game.mlx)
		return (puts(mlx_strerror(mlx_errno)), free_game(&game), EXIT_FAILURE);
	initialize_assets(&game);
	initialize_collectibles(&game);
	find_player_position(&game);
	draw_map(&game);
	mlx_key_hook(game.mlx, move_player, &game);
	mlx_close_hook(game.mlx, (mlx_closefunc)free_game, &game);
	mlx_loop_hook(game.mlx, animate_wall, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
