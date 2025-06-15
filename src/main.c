/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:10:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/06/15 17:01:37 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

// void update_jump(t_game *game, double delta_time)
// {
// 	if (game->player.is_jumping)
// 	{
// 		game->player.z_vel -= 9.8 * delta_time; // simulate gravity
// 		game->player.z += game->player.z_vel * delta_time;
// 		if (game->player.z <= 0)
// 		{
// 			game->player.z = 0;
// 			game->player.z_vel = 0;
// 			game->player.is_jumping = 0;
// 		}
// 	}
// }

static void	arg_checker(int ac, char **av)
{
	if (ac != 2 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
	{
		printf("Usage: ./cub3D <map.cub>\n");
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

bool cursor_visible = false;

void key_action(mlx_key_data_t keydata, void *param)
{
    t_game *game = (t_game *)param;

    if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
    {
        cursor_visible = !cursor_visible;

        if (cursor_visible)
            mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
        else
            mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
    }
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
	mlx_key_hook(game.mlx, &key_action, &game);

	// mlx_resize_hook(game.mlx, resize_callback, &game);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);

	init_player(&game);
	// render_mini_map(&game);

	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN); // optional: hide the mouse
	mlx_set_mouse_pos(game.mlx, 1920 / 2, 1080 / 2); // center it at start

	mlx_loop_hook(game.mlx, handle_input, &game);

	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_DISABLED); // disables cursor and captures mouse
	mlx_cursor_hook(game.mlx, handle_mouse_move, &game);

	mlx_loop(game.mlx);
	//free things
	// free_map(map.map);
	free_trims(&map);
	return (0);
}
