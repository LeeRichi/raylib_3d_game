/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:10:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/05/15 14:57:42 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	arg_checker(int ac, char **av)
{
	if (ac != 2)
	{
		printf("cub3D takes only one *.cub map as the second argument.");
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
	{
		printf("Error: only accepts file that end with .cub");
		exit(EXIT_FAILURE);
	}
}

static void game_init(t_game *game)
{
	game->mlx = mlx_init(1920, 1080, "cub3D", true);
	if (!game->mlx)
	{
		printf("Error: mlx_init failed");
		exit(EXIT_FAILURE);
	}
	game->img = mlx_new_image(game->mlx, 1920, 1080);
	if (!game->img)
	{
		printf("Error: mlx_new_image failed\n");
		exit(EXIT_FAILURE);
	}

	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
	{
		printf("Error: mlx_image_to_window failed");
		exit(EXIT_FAILURE);
	}
}

void init_player(t_game *game)
{
	t_map *map = game->map;
	int i = 0, j = 0;

	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			char c = map->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = j + 0.5;
				game->player.y = i + 0.5;

				if (c == 'N')
				{
					game->player.dir_x = 0;
					game->player.dir_y = -1;
					game->player.plane_x = 0.66;
					game->player.plane_y = 0;
				}
				else if (c == 'S')
				{
					game->player.dir_x = 0;
					game->player.dir_y = 1;
					game->player.plane_x = -0.66;
					game->player.plane_y = 0;
				}
				else if (c == 'E')
				{
					game->player.dir_x = 1;
					game->player.dir_y = 0;
					game->player.plane_x = 0;
					game->player.plane_y = 0.66;
				}
				else if (c == 'W')
				{
					game->player.dir_x = -1;
					game->player.dir_y = 0;
					game->player.plane_x = 0;
					game->player.plane_y = -0.66;
				}
				return ; // stop after finding the player
			}
			j++;
		}
		i++;
	}
}

void free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void free_trims(t_map *map)
{
	if (map->north_path)
		free(map->north_path);
	if (map->south_path)
		free(map->south_path);
	if (map->west_path)
		free(map->west_path);
	if (map->east_path)
		free(map->east_path);
}

void render_map(t_game *game)
{
	int w = game->img->width;
	int h = game->img->height;
	t_player *p = &game->player;
	t_map *map = game->map;

	for (int x = 0; x < w; x++)
	{
		// Calculate ray position and direction
		double camera_x = 2 * x / (double)w - 1;
		double ray_dir_x = p->dir_x + p->plane_x * camera_x;
		double ray_dir_y = p->dir_y + p->plane_y * camera_x;

		// Map grid position
		int map_x = (int)p->x;
		int map_y = (int)p->y;

		// Length of ray from one x or y side to next x or y side
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);

		double side_dist_x;
		double side_dist_y;

		int step_x;
		int step_y;

		int hit = 0; // wall hit flag
		int side;    // was a NS or EW wall hit?

		// Calculate step and initial side_dist
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

		// Perform DDA
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
			if (map->map[map_y][map_x] == '1')
				hit = 1;
		}

		// Calculate distance to wall
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (side_dist_x - delta_dist_x);
		else
			perp_wall_dist = (side_dist_y - delta_dist_y);

		// Calculate height of line to draw
		int line_height = (int)(h / perp_wall_dist);
		int draw_start = -line_height / 2 + h / 2;
		int draw_end = line_height / 2 + h / 2;

		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= h)
			draw_end = h - 1;

		// Choose color (simple flat)
		uint32_t color = (side == 1) ? 0x888888FF : 0xCCCCCCFF;

		// Draw vertical line
		for (int y = draw_start; y < draw_end; y++)
			mlx_put_pixel(game->img, x, y, color);
	}
}

void render_mini_map(t_game *game)
{
	uint32_t		x, y, i, j;
	uint32_t		tile_size = 64; // size of each block in pixels
	t_map	*map = game->map;

	for (i = 0; map->map[i]; i++)
	{
		for (j = 0; map->map[i][j]; j++)
		{
			char cell = map->map[i][j];
			uint32_t color = 0x000000FF; // default: transparent/black

			if (cell == '1')
				color = 0xFFFFFFFF; // white for wall
			else if (cell == '0')
				color = 0x808080FF; // gray for floor
			else if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
				color = 0xFF0000FF; // red for player

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

void clear_image(mlx_image_t *img)
{
    int w = img->width;
    int h = img->height;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            mlx_put_pixel(img, x, y, 0x000000FF);  // black color
}

void	handle_input(void *param)
{
	t_game	*game = (t_game *)param;
	t_player	*p = &game->player;
	mlx_t	*mlx = game->mlx;
	double	move_speed = 0.05;
	double	rot_speed = 0.05;

	// Clear the image before drawing
	clear_image(game->img);

	// Move forward
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		if (game->map->map[(int)(p->y)][(int)(p->x + p->dir_x * move_speed)] != '1')
			p->x += p->dir_x * move_speed;
		if (game->map->map[(int)(p->y + p->dir_y * move_speed)][(int)(p->x)] != '1')
			p->y += p->dir_y * move_speed;
	}

	// Move backward
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (game->map->map[(int)(p->y)][(int)(p->x - p->dir_x * move_speed)] != '1')
			p->x -= p->dir_x * move_speed;
		if (game->map->map[(int)(p->y - p->dir_y * move_speed)][(int)(p->x)] != '1')
			p->y -= p->dir_y * move_speed;
	}

	// Rotate right
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		double old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-rot_speed) - p->dir_y * sin(-rot_speed);
		p->dir_y = old_dir_x * sin(-rot_speed) + p->dir_y * cos(-rot_speed);
		double old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-rot_speed) - p->plane_y * sin(-rot_speed);
		p->plane_y = old_plane_x * sin(-rot_speed) + p->plane_y * cos(-rot_speed);
	}

	// Rotate left
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		double old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(rot_speed) - p->dir_y * sin(rot_speed);
		p->dir_y = old_dir_x * sin(rot_speed) + p->dir_y * cos(rot_speed);
		double old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(rot_speed) - p->plane_y * sin(rot_speed);
		p->plane_y = old_plane_x * sin(rot_speed) + p->plane_y * cos(rot_speed);
	}

	// Draw the new frame
	render_map(game);
}

int main(int ac, char **av)
{
	t_game	game;
	t_map	map;

	ft_bzero(&game, sizeof(t_game));
	ft_bzero(&map, sizeof(t_map));

	arg_checker(ac, av);
	game.map = &map;
	parse_map(av[1], &map);
	print_matrix(map.map);

	if (map_checker(&map))
	{
		//clean up
		free_map(map.map);
		exit(EXIT_FAILURE);
	}


	game_init(&game);
	init_player(&game);
	// render_mini_map(&game);
	mlx_loop_hook(game.mlx, handle_input, &game);
	mlx_loop(game.mlx);
	//free things
	// free_map(map.map);
	free_trims(&map);
	return (0);
}
