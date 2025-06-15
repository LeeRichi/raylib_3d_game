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

static void	arg_checker(int ac, char **av)
{
	if (ac != 2 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
	{
		printf("Usage: ./cub3D <map.cub>\n");
		exit(EXIT_FAILURE);
	}
}

void key_action(mlx_key_data_t keydata, void *param)
{
	t_game *game = (t_game *)param;
	bool cursor_visible = false;
	
    if (keydata.key == MLX_KEY_TAB && keydata.action == MLX_PRESS)
    {
        cursor_visible = !cursor_visible;

        if (cursor_visible)
            mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
        else
            mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
    }
}

int	main(int ac, char **av)
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
		free_map(map.map);
		free_trims(&map);
		exit(EXIT_FAILURE);
	}

	game_init(&game);
	init_player(&game);

	mlx_key_hook(game.mlx, &key_action, &game);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);

	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(game.mlx, 1920 / 2, 1080 / 2);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_DISABLED);

	mlx_loop_hook(game.mlx, handle_input, &game);
	mlx_cursor_hook(game.mlx, handle_mouse_move, &game);

	mlx_loop(game.mlx);

	clean_exit(&game, &map);
	return (0);
}