/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 05:26:49 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/03 21:16:37 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long_bonus.h"

char	*get_image_path(int index)
{
	static char	*paths[] = {
		"img/player_0.png",
		"img/player_1.png",
		"img/player_2.png",
		"img/player_3.png",
		"img/player_4.png",
		"img/player_5.png",
		"img/player_6.png",
		"img/player_7.png",
		"img/case_0.png",
		"img/case_1.png",
		"img/case_2.png",
		"img/case_3.png",
		"img/case_4.png",
		"img/case_5.png",
		"img/case_6.png",
		"img/case_7.png",
		"img/case_inv.png",
		"img/case_col.png",
		"img/wall.png",
		"img/wall2.png",
		"img/exit.png"
	};

	return (paths[index]);
}

void	exit_game(t_game *game, char *str)
{
	mlx_terminate(game->mlx);
	puts(str);
	free_game(game);
	exit(EXIT_FAILURE);
}

void	animate_wall(void *param)
{
	t_game		*game;
	static int	last_time;
	int			current_time;
	int			row;
	int			col;

	game = (t_game *)param;
	current_time = mlx_get_time();
	if (current_time - last_time >= 1)
	{
		last_time = current_time;
		if (game->cur_wall == 0)
			game->cur_wall = 1;
		else
			game->cur_wall = 0;
		row = -1;
		while (game->map[++row])
		{
			col = -1;
			while (game->map[row][++col])
				if (game->map[row][col] == '1')
					DRAW_IMG(game->mlx, game->assets.wall[game->cur_wall],
						col * T_S, row * T_S);
		}
	}
}
