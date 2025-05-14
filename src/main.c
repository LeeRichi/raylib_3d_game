/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:10:14 by chlee2            #+#    #+#             */
/*   Updated: 2025/05/14 12:04:09 by chlee2           ###   ########.fr       */
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

// static void game_init(char **av)
// {
// 	mlx_t	*mlx;
// 	(void)*av;
// 	mlx = mlx_init(1920, 1080, "cub3D", true);
// 	if (!mlx)
// 	{
// 		printf("Error: mlx_init failed");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(mlx, mlx_new_image(mlx, 1920, 1080), 0, 0) == 0)
// 	{
// 		printf("Error: mlx_image_to_window failed");
// 		exit(EXIT_FAILURE);
// 	}
// }

// void print_map(t_map map)
// {
// 	int i = 0;
// 	while (i < map.map_line_count)
// 	{
// 		printf("%s\n", map.map[i]);
// 		i++;
// 	}
// }

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

int main(int ac, char **av)
{
	t_game	game;
	t_map	map;

	ft_bzero(&game, sizeof(t_game));
	ft_bzero(&map, sizeof(t_map));

	arg_checker(ac, av);
	game.map = &map;
	parse_map(av[1], &map);

	// print_matrix(map.map);

	if (map_checker(&map))
	{
		//clean up
		free_map(map.map);
		exit(EXIT_FAILURE);
	}

	// game_init(av);

	//free things
	//free_map(map.map);
	return (0);
}
