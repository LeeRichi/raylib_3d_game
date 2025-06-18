/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:46:07 by chlee2            #+#    #+#             */
/*   Updated: 2025/06/15 16:50:14 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void calculate_ray_direction(t_game *game, int w)
{
    double camera_x;

	camera_x = 2 * game->x / (double)w - 1;
    game->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
    game->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
}

void render_map(t_game *game)
{
	int w = game->img->width;
	int h = game->img->height;
	t_player *p = &game->player;
	t_map *map = game->map;

	for (game->x = 0; game->x < w; game->x++)
	{
		calculate_ray_direction(game, w);

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
			if (game->map_y >= 0 && game->map_y < map->map_line_count &&
				game->map_x >= 0 && game->map_x < (int)ft_strlen(map->map[game->map_y]) &&
				map->map[game->map_y][game->map_x] == '1')
				game->hit = 1;
		}

		game->perp_wall_dist = (game->side == 0)
			? (game->side_dist_x - game->delta_dist_x)
			: (game->side_dist_y - game->delta_dist_y);

		if (game->perp_wall_dist < 1e-6)
			game->perp_wall_dist = 1e-6;

		int line_height = (int)(h / game->perp_wall_dist);
		game->line_height = (int)(h / game->perp_wall_dist);

		int draw_start = -line_height / 2 + h / 2;
		int draw_end = game->line_height / 2 + h / 2;
		if (draw_start < 0) draw_start = 0;
		if (draw_end >= h) draw_end = h - 1;

		mlx_texture_t *tex;
		if (game->side == 0 && game->ray_dir_x < 0)
			tex = game->textures->w_wall_texture;
		else if (game->side == 0 && game->ray_dir_x >= 0)
			tex = game->textures->e_wall_texture;
		else if (game->side == 1 && game->ray_dir_y < 0)
			tex = game->textures->n_wall_texture;
		else
			tex = game->textures->s_wall_texture;

		double wall_x;
		if (game->side == 0)
			wall_x = p->y + game->perp_wall_dist * game->ray_dir_y;
		else
			wall_x = p->x + game->perp_wall_dist * game->ray_dir_x;
		wall_x -= floor(wall_x);

		uint32_t tex_x = (int)(wall_x * (double)(tex->width));

		tex_x = tex_x < 0 ? 0 : tex_x;
		tex_x = tex_x >= tex->width ? tex->width - 1 : tex_x;

		if ((game->side == 0 && game->ray_dir_x > 0) || (game->side == 1 && game->ray_dir_y < 0))
			tex_x = tex->width - tex_x - 1;

		// STEP and texture coordinate setup
		double step = 1.0 * tex->height / game->line_height;
		double tex_pos = (draw_start - h / 2 + game->line_height / 2) * step;

		for (int y = draw_start; y < draw_end; y++)
		{
			uint32_t tex_y = (int)tex_pos;
			tex_pos += step;
			
			//boundary check
			if (tex_y < 0) tex_y = 0;
			if (tex_y >= tex->height) tex_y = tex->height - 1;

			int i = (tex_y * tex->width + tex_x) * 4;
			uint8_t r = tex->pixels[i];
			uint8_t g = tex->pixels[i + 1];
			uint8_t b = tex->pixels[i + 2];
			uint8_t a = tex->pixels[i + 3];

			mlx_put_pixel(game->img, game->x, y, (r << 24 | g << 16 | b << 8 | a));
		}

		//old
		// for (int y = draw_start; y < draw_end; y++)
		// {
		// 	int d = y * 256 - h * 128 + line_height * 128;
			
		// 	int tex_y = ((d * tex->height) / line_height) / 256;

		// 	int i = (tex_y * tex->width + tex_x) * 4;
		// 	uint8_t r = tex->pixels[i];
		// 	uint8_t g = tex->pixels[i + 1];
		// 	uint8_t b = tex->pixels[i + 2];
		// 	uint8_t a = tex->pixels[i + 3];

		// 	mlx_put_pixel(game->img, x, y, (r << 24 | g << 16 | b << 8 | a));
		// }
	}
}


// // void render_mini_map(t_game *game)
// // {
// // 	uint32_t		x, y, i, j;
// // 	uint32_t		tile_size = 64; // size of each block in pixels
// // 	t_map	*map = game->map;

// // 	for (i = 0; map->map[i]; i++)
// // 	{
// // 		for (j = 0; map->map[i][j]; j++)
// // 		{
// // 			char cell = map->map[i][j];
// // 			uint32_t color = 0x000000FF; // default: transparent/black

// // 			if (cell == '1')
// // 				color = 0xFFFFFFFF; // white for wall
// // 			else if (cell == '0')
// // 				color = 0x808080FF; // gray for floor
// // 			else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
// // 				color = 0xFF0000FF; // red for player

// // 			// Draw tile as a square of pixels
// // 			for (y = 0; y < tile_size; y++)
// // 			{
// // 				for (x = 0; x < tile_size; x++)
// // 				{
// // 					uint32_t px = j * tile_size + x;
// // 					uint32_t py = i * tile_size + y;
// // 					if (px < game->img->width && py < game->img->height)
// // 						mlx_put_pixel(game->img, px, py, color);
// // 				}
// // 			}
// // 		}
// // 	}
// // }
