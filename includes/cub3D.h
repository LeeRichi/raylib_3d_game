/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:12:45 by chlee2            #+#    #+#             */
/*   Updated: 2025/05/13 11:53:35 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

#ifndef MAX_LINES
# define MAX_LINES 1024
#endif


typedef struct s_map
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_color;
	int		ceiling_color;
	char	**map; //this is map that extends with white spaces to make it rectangular
	int		map_line_count;
	int		player_pos_x;
	int		player_pos_y;
}	t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	// Add player info, texture paths, etc.
}	t_game;


//src/parse_map
void	parse_map(const char *map_path, t_map *map);
//src/parse_map/save_map.c
void	save_map(t_map *map, char **map_lines);
//src/parse_map/save_color.c
void	save_color(t_map *map, char *line);
//src/parse_map/save_texture.c
void	save_texture(t_map *map, char *line);

int		map_checker(t_map *map);

//utils.c
void	malloc_fail_exit(void);
void	free_matrix(char **matrix);
void	error_exit(char *reason);
void	free_lines_count(char **lines, int count);
void	print_matrix(char **matrix);

#endif
