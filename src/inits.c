/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 23:42:40 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/01 02:56:34 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

mlx_image_t	*load_image(mlx_t *mlx, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
	{
		puts("Error: Failed to load texture");
		return (NULL);
	}
	image = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	return (image);
}

void	initialize_assets(t_game *game)
{
	game->assets.player = load_image(game->mlx, "img/player_0.png");
	game->assets.c_0 = load_image(game->mlx, "img/case_0.png");
	game->assets.c_col = load_image(game->mlx, "img/case_col.png");
	game->assets.wall = load_image(game->mlx, "img/wall.png");
	game->assets.exit = load_image(game->mlx, "img/exit.png");
	if (!game->assets.player || !game->assets.c_0 || !game->assets.c_col
		|| !game->assets.wall || !game->assets.exit)
	{
		mlx_terminate(game->mlx);
		puts("Error: Failed to load one or more images");
		free_game(game);
		exit(EXIT_FAILURE);
	}
}

void	initialize_collectibles(t_game *game)
{
	int	row;
	int	col;

	game->collectibles = 0;
	row = 0;
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
		{
			if (game->map[row][col] == 'C')
				game->collectibles++;
			col++;
		}
		row++;
	}
}

void	initialize_window_size(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (game->map[row])
	{
		while (game->map[row][col])
			col++;
		row++;
	}
	game->win_width = col * T_S;
	game->win_height = row * T_S;
	game->move_count = 0;
}
