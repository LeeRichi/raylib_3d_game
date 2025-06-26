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

void	skip_spaces(char **map, int *i, int *j)
{
	while (map[*i][*j] == ' ' || map[*i][*j] == '\t'
		|| map[*i][*j] == '\r'
		|| map[*i][*j] == '\v' || map[*i][*j] == '\f')
		(*j)++;
}

static void	arg_checker(int ac, char **av)
{
	if (ac != 2 || ft_strncmp(av[1] + ft_strlen(av[1]) - 4, ".cub", 4))
	{
		printf("Usage: ./cub3D <map.cub>\n");
		exit(EXIT_FAILURE);
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
	if (map_checker(&map))
	{
		free_map(map.map);
		free_trims(&map);
		exit(EXIT_FAILURE);
	}
	game_init(&game);
	init_player(&game);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	mlx_set_cursor_mode(game.mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(game.mlx, handle_input, &game);
	mlx_cursor_hook(game.mlx, handle_mouse_move, &game);
	mlx_loop(game.mlx);
	clean_exit(&game, &map);
	return (0);
}
