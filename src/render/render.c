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


// void calculate_ray_direction(t_game *game, int w)
// {
//     double camera_x;
// 	camera_x = 2 * game->x / (double)w - 1;
//     game->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
//     game->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
// }

// void help(t_game *game, int *map_x, int *map_y)
// {
// 	double side_dist_x;
// 	double side_dist_y;

// 	int step_x = 0;
// 	int step_y = 0;

// 	int hit = 0; // wall hit flag

// 	// Calculate step and initial side_dist
// 	if (*game->ray_dir_x < 0)
// 	{
// 		step_x = -1;
// 		side_dist_x = (game->player.x - *map_x) * fabs(1 / *game->ray_dir_x);
// 	}
// 	else
// 	{
// 		step_x = 1;
// 		side_dist_x = (*map_x + 1.0 - game->player.x) * fabs(1 / *game->ray_dir_x);
// 	}
// 	if (game->game->ray_dir_y < 0)
// 	{
// 		step_y = -1;
// 		side_dist_y = (game->player.y - *map_y) * fabs(1 / game->game->ray_dir_y);
// 	}
// 	else
// 	{
// 		step_y = 1;
// 		side_dist_y = (*map_y + 1.0 - game->player.y) * fabs(1 / game->game->ray_dir_y);
// 	}
// }

// void render_map(t_game *game)
// {
// 	int		map_x;
// 	int		map_y;
// 	// double	ray_dir_x;
// 	// double	ray_dir_y;
	
// 	// int		side;


// 	for (game->x = 0; game->x < game->img->width; game->x++)
// 	{
// 		calculate_ray_direction(game, game->img->width);
// 		map_x = (int)game->player.x;
// 		map_y = (int)game->player.y;

// 		// help(game, &map_x, &map_y);

// 		// double side_dist_x;
// 		double side_dist_y;

// 		int step_x;
// 		int step_y;

// 		int hit = 0; // wall hit flag
// 		int side = 0;    // was a NS or EW wall hit?

// 		// Calculate step and initial side_dist
// 		if (game->ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			game->side_dist_x = (game->player.x - map_x) * fabs(1 / game->ray_dir_x);
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			game->side_dist_x = (map_x + 1.0 - game->player.x) * fabs(1 / game->ray_dir_x);
// 		}
// 		if (game->ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (game->player.y - map_y) * fabs(1 / game->ray_dir_y);
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - game->player.y) * fabs(1 / game->ray_dir_y);
// 		}

// 		// Perform DDA
// 		while (!hit)
// 		{
// 			if (game->side_dist_x < side_dist_y)
// 			{
// 				game->side_dist_x += fabs(1 / game->ray_dir_x);
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += fabs(1 / game->ray_dir_y);
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (map_y >= 0 && map_y < game->map->map_line_count &&
// 				map_x >= 0 && map_x < (int)ft_strlen(game->map->map[map_y]) &&
// 				game->map->map[map_y][map_x] == '1')
// 				hit = 1;
// 		}

// 		// Calculate distance to wall
// 		double perp_wall_dist;
// 		if (side == 0)
// 			perp_wall_dist = (game->side_dist_x - fabs(1 / game->ray_dir_x));
// 		else
// 			perp_wall_dist = (side_dist_y - fabs(1 / game->ray_dir_y));

// 		// if (perp_wall_dist < 0.05)
// 		// {
// 		// 	printf("hi\n");
// 		// 	perp_wall_dist = 0.1;
// 		// }
// 		int line_height = (int)(game->img->height / perp_wall_dist);

// 		int cam_offset = 0;
// 		// int cam_offset = -(int)(game->player.z * 100); // adjust scale to match visual

// 		int draw_start = -line_height / 2 + game->img->height / 2 + cam_offset;
// 		uint32_t draw_end = line_height / 2 + game->img->height / 2 + cam_offset;

// 		if (draw_start < 0)
// 			draw_start = 0;
// 		if (draw_end >= game->img->height)
// 			draw_end = game->img->height - 1;

// 		mlx_texture_t *tex;
// 		if (side == 0 && game->ray_dir_x < 0)
// 			tex = game->textures->w_wall_texture;
// 		else if (side == 0 && game->ray_dir_x >= 0)
// 			tex = game->textures->e_wall_texture;
// 		else if (side == 1 && game->ray_dir_y < 0)
// 			tex = game->textures->n_wall_texture;
// 		else
// 			tex = game->textures->s_wall_texture;

// 		double wall_x;
// 		if (side == 0)
// 			wall_x = game->player.y + perp_wall_dist * game->ray_dir_y;
// 		else
// 			wall_x = game->player.x + perp_wall_dist * game->ray_dir_x;
// 		wall_x -= floor(wall_x);  // 0.0 to 1.0

// 		int tex_x = (int)(wall_x * (double)(tex->width));
// 		if ((side == 0 && game->ray_dir_x > 0) || (side == 1 && game->ray_dir_y < 0))
// 			tex_x = tex->width - tex_x - 1;

// 		for (uint32_t y = draw_start; y < draw_end; y++)
// 		{
// 			int d = y * 256 - game->img->height * 128 + line_height * 128;
// 			int tex_y = ((d * tex->height) / line_height) / 256;

// 			int i = (tex_y * tex->width + tex_x) * 4;
// 			uint8_t r = tex->pixels[i];
// 			uint8_t g = tex->pixels[i + 1];
// 			uint8_t b = tex->pixels[i + 2];
// 			uint8_t a = tex->pixels[i + 3];

// 			mlx_put_pixel(game->img, game->x, y, (r << 24 | g << 16 | b << 8 | a));
// 		}
// 	}
// }


void render_map(t_game *game)
{
	int w = game->img->width;
	int h = game->img->height;
	t_player *p = &game->player;
	t_map *map = game->map;

	for (int x = 0; x < w; x++)
	{
		double camera_x = 2 * x / (double)w - 1;
		double ray_dir_x = p->dir_x + p->plane_x * camera_x;
		double ray_dir_y = p->dir_y + p->plane_y * camera_x;

		int map_x = (int)p->x;
		int map_y = (int)p->y;

		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double side_dist_x;
		double side_dist_y;

		int step_x, step_y, hit = 0, side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (p->x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - p->x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (p->y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - p->y) * delta_dist_y;
		}

		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_y >= 0 && map_y < map->map_line_count &&
				map_x >= 0 && map_x < (int)ft_strlen(map->map[map_y]) &&
				map->map[map_y][map_x] == '1')
				hit = 1;
		}

		double perp_wall_dist = (side == 0)
			? (side_dist_x - delta_dist_x)
			: (side_dist_y - delta_dist_y);

		if (perp_wall_dist < 1e-6)
			perp_wall_dist = 1e-6;

		int line_height = (int)(h / perp_wall_dist);

		int draw_start = -line_height / 2 + h / 2;
		int draw_end = line_height / 2 + h / 2;
		if (draw_start < 0) draw_start = 0;
		if (draw_end >= h) draw_end = h - 1;

		mlx_texture_t *tex;
		if (side == 0 && ray_dir_x < 0)
			tex = game->textures->w_wall_texture;
		else if (side == 0 && ray_dir_x >= 0)
			tex = game->textures->e_wall_texture;
		else if (side == 1 && ray_dir_y < 0)
			tex = game->textures->n_wall_texture;
		else
			tex = game->textures->s_wall_texture;

		double wall_x;
		if (side == 0)
			wall_x = p->y + perp_wall_dist * ray_dir_y;
		else
			wall_x = p->x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		uint32_t tex_x = (int)(wall_x * (double)(tex->width));

		tex_x = tex_x < 0 ? 0 : tex_x;
		tex_x = tex_x >= tex->width ? tex->width - 1 : tex_x;

		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = tex->width - tex_x - 1;


		// STEP and texture coordinate setup
		double step = 1.0 * tex->height / line_height;
		double tex_pos = (draw_start - h / 2 + line_height / 2) * step;

		for (int y = draw_start; y < draw_end; y++)
		{
			uint32_t tex_y = (int)tex_pos;
			tex_pos += step;

			if (tex_y < 0) tex_y = 0;
			if (tex_y >= tex->height) tex_y = tex->height - 1;

			int i = (tex_y * tex->width + tex_x) * 4;
			uint8_t r = tex->pixels[i];
			uint8_t g = tex->pixels[i + 1];
			uint8_t b = tex->pixels[i + 2];
			uint8_t a = tex->pixels[i + 3];

			mlx_put_pixel(game->img, x, y, (r << 24 | g << 16 | b << 8 | a));
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







//old version before nor,
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

// #include "../../includes/cub3D.h"

// void render_map(t_game *game)
// {
// 	int w = game->img->width;
// 	int h = game->img->height;
// 	t_player *p = &game->player;
// 	t_map *map = game->map;

// 	for (int x = 0; x < w; x++)
// 	{
// 		// Calculate ray position and direction
// 		double camera_x = 2 * x / (double)w - 1;
// 		double ray_dir_x = p->dir_x + p->plane_x * camera_x;
// 		double ray_dir_y = p->dir_y + p->plane_y * camera_x;

// 		// Map grid position
// 		int map_x = (int)p->x;
// 		int map_y = (int)p->y;

// 		// Length of ray from one x or y side to next x or y side
// 		double delta_dist_x = fabs(1 / ray_dir_x);
// 		double delta_dist_y = fabs(1 / ray_dir_y);

// 		double side_dist_x;
// 		double side_dist_y;

// 		int step_x;
// 		int step_y;

// 		int hit = 0; // wall hit flag
// 		int side;    // was a NS or EW wall hit?

// 		// Calculate step and initial side_dist
// 		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (p->x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - p->x) * delta_dist_x;
// 		}
// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (p->y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - p->y) * delta_dist_y;
// 		}

// 		// Perform DDA
// 		while (!hit)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (map_y >= 0 && map_y < map->map_line_count &&
// 				map_x >= 0 && map_x < (int)ft_strlen(map->map[map_y]) &&
// 				map->map[map_y][map_x] == '1')
// 				hit = 1;
// 		}

// 		// Calculate distance to wall
// 		double perp_wall_dist;
// 		if (side == 0)
// 			perp_wall_dist = (side_dist_x - delta_dist_x);
// 		else
// 			perp_wall_dist = (side_dist_y - delta_dist_y);

// 		int line_height = (int)(h / perp_wall_dist);

// 		int cam_offset = 0;
// 		// int cam_offset = -(int)(game->player.z * 100); // adjust scale to match visual

// 		int draw_start = -line_height / 2 + h / 2 + cam_offset;
// 		int draw_end = line_height / 2 + h / 2 + cam_offset;

// 		if (draw_start < 0)
// 			draw_start = 0;
// 		if (draw_end >= h)
// 			draw_end = h - 1;

// 		mlx_texture_t *tex;
// 		if (side == 0 && ray_dir_x < 0)
// 			tex = game->textures->w_wall_texture;
// 		else if (side == 0 && ray_dir_x >= 0)
// 			tex = game->textures->e_wall_texture;
// 		else if (side == 1 && ray_dir_y < 0)
// 			tex = game->textures->n_wall_texture;
// 		else
// 			tex = game->textures->s_wall_texture;

// 		double wall_x;
// 		if (side == 0)
// 			wall_x = p->y + perp_wall_dist * ray_dir_y;
// 		else
// 			wall_x = p->x + perp_wall_dist * ray_dir_x;
// 		wall_x -= floor(wall_x);  // 0.0 to 1.0

// 		int tex_x = (int)(wall_x * (double)(tex->width));
// 		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
// 			tex_x = tex->width - tex_x - 1;

// 		for (int y = draw_start; y < draw_end; y++)
// 		{
// 			int d = y * 256 - h * 128 + line_height * 128;
// 			int tex_y = ((d * tex->height) / line_height) / 256;

// 			int i = (tex_y * tex->width + tex_x) * 4;
// 			uint8_t r = tex->pixels[i];
// 			uint8_t g = tex->pixels[i + 1];
// 			uint8_t b = tex->pixels[i + 2];
// 			uint8_t a = tex->pixels[i + 3];

// 			mlx_put_pixel(game->img, x, y, (r << 24 | g << 16 | b << 8 | a));
// 		}
// 	}
// }

// void render_mini_map(t_game *game)
// {
// 	uint32_t		x, y, i, j;
// 	uint32_t		tile_size = 64; // size of each block in pixels
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