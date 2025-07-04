/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:46:07 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/04 20:10:08 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// void render_mini_map(t_game *game)
// {
// 	uint32_t		x, y, i, j;
// 	uint32_t		tile_size = 8; // size of each block in pixels
// 	t_map	*map = game->map;

// 	for (i = 0; map->map[i]; i++)
// 	{
// 		for (j = 0; map->map[i][j]; j++)
// 		{
// 			char cell = map->map[i][j];
// 			uint32_t color = 0x000000FF; // default: transparent/black

// 			if (cell == '1')
// 				color = 0xFFFFFFFF; // white for wall
// 			else if (cell == '0')
// 				color = 0x808080FF; // gray for floor
// 			else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
// 				color = 0xFF0000FF; // red for player

// 			// Draw tile as a square of pixels
// 			for (y = 0; y < tile_size; y++)
// 			{
// 				for (x = 0; x < tile_size; x++)
// 				{
// 					uint32_t px = j * tile_size + x;
// 					uint32_t py = i * tile_size + y;
// 					if (px < game->img->width && py < game->img->height)
// 						mlx_put_pixel(game->img, px, py, color);
// 				}
// 			}
// 		}
// 	}
// }


void render_mini_map(t_game *game)
{
	uint32_t		x, y, i, j;
	uint32_t		tile_size = 14; // size of each block in pixels
	t_map	*map = game->map;

	for (i = 0; map->map[i]; i++)
	{
		for (j = 0; map->map[i][j]; j++)
		{
			char cell = map->map[i][j];
			uint32_t color = 0x000000FF; // default: transparent/black

			if (cell == '1')
				color = 0xFFFFFFFF; // white for wall
			else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
				color = 0xFF0000FF; // red for player
			else
				color = 0x808080FF; // gray for floor

			// Draw tile as a square of pixels
			for (y = 0; y < tile_size; y++)
			{
				for (x = 0; x < tile_size; x++)
				{
					uint32_t px = j * tile_size + x;
					uint32_t py = i * tile_size + y;
					if (px < game->img->width && py < game->img->height)
						mlx_put_pixel(game->img, px, py, color);
				}
			}
		}
	}
}


void render_mini_map(t_game *game, t_map *map)
{
	int			i;
	int			j;
	int			rad;
	uint32_t	color;
	
	i = map->player_pos_x - rad;
	j = map->player_pos_y - rad;
	while (i <= map->player_pos_x + rad)
	{
		while (j <= map->player_pos_y + rad)
		{
			if (i < 0 || j < 0 
			|| i > map->player_pos_x + rad || j > map->player_pos_y + rad)
				color = 0x03B1FCFF; //#fcb103
			else
			{
				if (map[i][j] == '1')
					color = 0xFFFFFF00;
				else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
					color = 0x2C03FCFF;//#fc032c
				else if map[i][j] == '0'
					color = 0xFFFFFFFF;
				else
					color = 0x03B1FCFF;
				draw_minimap_block(game, i )	
			}
		}
	}	
}
