/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:46:07 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/10 19:57:08 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

void	calculate_ray_direction(t_game *game, int w)
{
	double	camera_x;

	camera_x = 2 * game->x / (double)w - 1;
	game->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	game->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
}

void	setup_dda(t_game *game, t_player *p)
{
	game->map_x = (int)p->x;
	game->map_y = (int)p->y;
	game->delta_dist_x = fabs(1 / game->ray_dir_x);
	game->delta_dist_y = fabs(1 / game->ray_dir_y);
	game->hit = 0;
	if (game->ray_dir_x < 0)
	{
		game->step_x = -1;
		game->side_dist_x = (p->x - game->map_x) * game->delta_dist_x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist_x = (game->map_x + 1.0 - p->x) * game->delta_dist_x;
	}
	if (game->ray_dir_y < 0)
	{
		game->step_y = -1;
		game->side_dist_y = (p->y - game->map_y) * game->delta_dist_y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist_y = (game->map_y + 1.0 - p->y) * game->delta_dist_y;
	}
}

void	perform_dda(t_game *game, t_map *map)
{
	while (!game->hit)
	{
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x += game->delta_dist_x;
			game->map_x += game->step_x;
			game->side = 0;
		}
		else
		{
			game->side_dist_y += game->delta_dist_y;
			game->map_y += game->step_y;
			game->side = 1;
		}
		if (game->map_y >= 0 && game->map_y < map->map_line_count
			&& game->map_x >= 0 && game->map_x
			< (int)ft_strlen(map->map[game->map_y])
			&& map->map[game->map_y][game->map_x] == '1')
			game->hit = 1;
	}
}
