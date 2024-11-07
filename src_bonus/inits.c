/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 23:42:40 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/02 22:43:48 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
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

void	load_images(t_game *game)
{
	int	i;

	i = 0;
	while (i <= 7)
	{
		game->assets.p[i] = load_image(game->mlx, get_image_path(i));
		i++;
	}
	i = 0;
	while (i <= 7)
	{
		game->assets.c[i] = load_image(game->mlx, get_image_path(i + 8));
		i++;
	}
	game->assets.c_inv = load_image(game->mlx, get_image_path(16));
	game->assets.c_col = load_image(game->mlx, get_image_path(17));
	game->assets.wall[0] = load_image(game->mlx, get_image_path(18));
	game->assets.wall[1] = load_image(game->mlx, get_image_path(19));
	game->assets.exit = load_image(game->mlx, get_image_path(20));
}

void	initialize_assets(t_game *game)
{
	int	i;

	i = 0;
	load_images(game);
	while (i <= 7)
	{
		if (!game->assets.p[i])
			exit_game(game, "Error: Failed to load one or more player images");
		i++;
	}
	i = 0;
	while (i <= 7)
	{
		if (!game->assets.c[i])
			exit_game(game, "Error: Failed to load one or more cases images");
		i++;
	}
	if (!game->assets.wall[0] || !game->assets.wall[1]
		|| !game->assets.c_col || !game->assets.c_inv || !game->assets.exit)
		exit_game(game, "Error: Failed to load one or more usefull images");
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
	while (game->map[row])
	{
		col = 0;
		while (game->map[row][col])
			col++;
		row++;
	}
	game->win_width = col * T_S;
	game->win_height = row * T_S;
	game->move_count = 0;
	game->cur_wall = 0;
}
