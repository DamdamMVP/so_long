/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 04:59:23 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/03 21:13:21 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define BUFFER_SIZE 1024
#define WIDTH 1280
#define HEIGHT 720
#define T_S 40
#define DRAW_IMG mlx_image_to_window

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "MLX42/MLX42.h"

typedef struct s_elements
{
	int	p;
	int	e;
	int	c;
}	t_elements;

typedef struct s_assets
{
	mlx_image_t	*p[8];
	mlx_image_t	*c[8];
	mlx_image_t	*c_inv;
	mlx_image_t	*c_col;
	mlx_image_t	*wall[2];
	mlx_image_t	*exit;
}	t_assets;

typedef struct s_game
{
	mlx_t			*mlx;
	t_assets		assets;
	mlx_image_t		*prev_img;
	mlx_image_t		*cur_p;
	char			**map;
	int				p_row;
	int				p_col;
	int				collectibles;
	int				win_width;
	int				win_height;
	int				move_count;
	int				cur_wall;
}	t_game;

// __ TO REPLACE
void	find_p_0_position(t_game *game);
void	free_game(t_game *game);
void	animate_wall(void *param);

// __ updates.c
void	update_prev_image(t_game *game, int new_row, int new_col);
void	update_player_icon(t_game *game);
void	update_case_icon(t_game *game, int row, int col);

// __ utils.c
char	*get_image_path(int index);
void	exit_game(t_game *game, char *str);

// __ key_actions
void	move_player(mlx_key_data_t keydata, void *param);

// __ draw.c
void	draw_tile(t_game *game, char tile, int col, int row);
void	draw_map(t_game *game);

// __ handle_assets.c
void	handle_player_movement(t_game *game, int new_row, int new_col);
void	handle_collectible(t_game *game, int new_row, int new_col);
void	handle_exit(t_game *game);
void	handle_default(t_game *game);

// __ inits.c
void	initialize_assets(t_game *game);
void	initialize_collectibles(t_game *game);
void	initialize_window_size(t_game *game);

// __ is_valid_map.c
int		is_valid_map(char **map);
int		is_valid_char(char **map);
int		is_map_rect(char **map);
int		is_map_close(char **map);
int		have_require_elem(char **map);

// __ can_be_finish.c
int		can_be_finish(char **map);
void	flood_fill(char **map, int row, int col);
