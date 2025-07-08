/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:46:07 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/07 23:27:08 by wweerasi         ###   ########.fr       */
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


// void render_mini_map(t_game *game)
// {
// 	uint32_t		x, y, i, j;
// 	uint32_t		tile_size = 14; // size of each block in pixels
// 	t_map	*map = game->map;

// 	for (i = 0; map->map[i]; i++)
// 	{
// 		for (j = 0; map->map[i][j]; j++)
// 		{
// 			char cell = map->map[i][j];
// 			uint32_t color = 0x000000FF; // default: transparent/black

// 			if (cell == '1')
// 				color = 0xFFFFFFFF; // white for wall
// 			else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
// 				color = 0xFF0000FF; // red for player
// 			else
// 				color = 0x808080FF; // gray for floor

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

static void	draw_sq_block(t_game *game, int x, int y, uint32_t clr)
{
	int	blk_x;
	int	blk_y;
	int	blk_size;
	uint32_t	*pixels;
	uint32_t	blk_stpos;
	
	printf("inside draw block\n");
	pixels = (uint32_t *)game->img->pixels;
	blk_size = 16;
	blk_y = 1;
	blk_stpos = ((game->img->height - y * blk_size) * (int)game->img->width) + (x * blk_size);
	while (blk_y < blk_size)
	{
		blk_x = 1;
		while (blk_x < blk_size)
		{
			pixels[blk_stpos + blk_x] = clr;
			blk_x++;
		}
		blk_stpos += (int)game->img->width;
		blk_y++;
	}
}

static uint32_t	set_block_color(t_map *map_data, int i, int j, int rad)
{
	char **map;

	map = map_data-> map;
	if (i < 0 || j < 0 || i > map_data->player_pos_x + rad 
		|| j > map_data->player_pos_y + rad)
		return (0x03B1FCFF); //#fcb103
	if (map[i][j] == '1')
		return (0xFFFFFF00);
	else if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
		|| map[i][j] == 'W')
		return (0x2C03FCFF);//#fc032c
	else if (map[i][j] == '0')
		return (0xFFFFFFFF);
	else
		return (0x03B1FCFF);
}

void render_minimap(t_game *game, t_player	*p, int x, int y)
{
	int			i;
	int			j;
	int			rad;
	uint32_t	color;
	
	rad = 7;
	i = floor(p->x) - rad - 1;
	j = floor(p->y) - rad - 1;
	while (j <= floor(p->y) + rad)
	{
		while (i <= floor(p->x) + rad)
		{
			color = set_block_color(game -> map, i, j, rad);
			draw_sq_block(game, x, y, color);
			j++;
			x++;
			if ((uint32_t)x > game->img->width)
				break;
		}
		i++;
		y--;
		if (y < 0)
			break;
	}
}
