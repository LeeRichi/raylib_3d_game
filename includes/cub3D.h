/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:12:45 by chlee2            #+#    #+#             */
/*   Updated: 2025/06/15 23:34:51 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include <math.h>

#ifndef MAX_LINES
# define MAX_LINES 1024
#endif

#ifndef TEX_WIDTH
#define TEX_WIDTH 64
#endif
#ifndef TEX_HEIGHT
#define TEX_HEIGHT 64
#endif

//**map is map that extends with white spaces to make it rectangular
typedef struct s_map
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	int		floor_color;
	int		ceiling_color;
	char	**map;

	int		map_line_count;
	int		coloum_count;

	int		player_pos_x;
	int		player_pos_y;
}	t_map;

typedef struct s_player {
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_textures {
	mlx_texture_t	*n_wall_texture;
	mlx_texture_t	*e_wall_texture;
	mlx_texture_t	*s_wall_texture;
	mlx_texture_t	*w_wall_texture;
	mlx_image_t 	*n_wall_img;
	mlx_image_t 	*e_wall_img;
	mlx_image_t 	*s_wall_img;
	mlx_image_t 	*w_wall_img;
	uint32_t *pixels;
    int32_t width;
    int32_t height;
}	t_textures;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	t_player	player;
	t_textures	*textures;
	int			tab_mode;
	int			skip_mouse_frame;
	double		last_mouse_x;

	mlx_image_t *pause_text;
    mlx_image_t *resume_text;
	mlx_image_t *pause_overlay;

	uint32_t	x;
	// uint32_t	y;

	double	ray_dir_x;
	double	ray_dir_y;
	
	double	side_dist_x;
	double	side_dist_y;

	int step_x;
	int step_y;

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

//game_init.c
void	game_init(t_game *game);
//player_init.c
void	init_player(t_game *game);

//render/render.c
void	render_map(t_game *game);
void	render_mini_map(t_game *game);

//src/handler/keyboard_handler.c
void	handle_input(void *param);
//src/handler/mouse_handler.c
void	handle_mouse_move(double xpos, double ypos, void *param);

//clean
void	free_map(char **map);
void	free_trims(t_map *map);
void	free_images(t_game *game);
void	free_textures(t_game *game);
void	clean_exit(t_game *game, t_map *map);


void	is_tab_mode(t_game *game);


//src/render/render_pausre.c
void	render_pause_screen(t_game *game, int show);


#endif
