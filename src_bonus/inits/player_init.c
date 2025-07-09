/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:10:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/09 23:27:23 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

void	position_ns(t_game *game, double dir_y, double plane_x)
{
	game->player.dir_x = 0;
	game->player.dir_y = dir_y;
	game->player.plane_x = plane_x;
	game->player.plane_y = 0;
}

void	position_ew(t_game *game, double dir_x, double plane_y)
{
	game->player.dir_x = dir_x;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = plane_y;
}

void	set_pos(char c, t_game *game)
{
	if (c == 'N')
		position_ns(game, -1, 0.66);
	else if (c == 'S')
		position_ns(game, 1, -0.66);
	else if (c == 'E')
		position_ew(game, 1, 0.66);
	else if (c == 'W')
		position_ew(game, -1, -0.66);
}

void	init_player(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while (game->map->map[i])
	{
		j = 0;
		while (game->map->map[i][j])
		{
			c = game->map->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;
				set_pos(c, game);
				return ;
			}
			j++;
		}
		i++;
	}
}
