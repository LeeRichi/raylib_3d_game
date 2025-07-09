/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:46:07 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/09 15:22:04 by wweerasi         ###   ########.fr       */
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

static uint32_t	set_block_color(t_game *game, int i, int j, int rad)
{
	char **map;
	t_player	*p;
	(void) rad;

	map = game -> map-> map;
	p = &game -> player;
	if (i < 0 || j < 0 || i >= game->map->coloum_count 
		|| j >= game->map->map_line_count)
	{
		return (0xFFB5BEB2); //#fcb103
	}
	else if (map[j][i] == '1')
		return (0xFF000000);
	else if (i == (int) floor(p->x) && j == (int) floor(p->y))
		return (0xFF0000FF);//#fc032c
	else if (map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E' || map[j][i] == 'W')
		return (0xFFFFFFFF);
	else
		return (0xFFB5BEB2);
}

void render_minimap(t_game *game, t_player	*p, int x, int y)
{
	int			i;
	int			j;
	int			rad;
	uint32_t	color;
	
	rad = 7;
	i = (int) floor(p->x) - rad;
	j = (int) floor(p->y) - rad;
	
	while (j < (int) floor(p->y) + rad + 1)
	{
		i = (int) floor(p->x) - rad;
		x = 0; 
		while (i < (int) floor(p->x) + rad + 1)
		{
			color = set_block_color(game, i, j, rad);
			draw_sq_block(game, x, y, color);
			i++;
			x++;
		}
		j++;
		y--;
	}
}
