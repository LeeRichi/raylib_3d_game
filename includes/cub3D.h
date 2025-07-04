/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:12:45 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/04 23:38:47 by wweerasi         ###   ########.fr       */
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

# ifndef MAX_LINES
#  define MAX_LINES 500//why this amount for both max column size and row size
# endif

# ifndef TEX_WIDTH
#  define TEX_WIDTH 64
# endif

# ifndef TEX_HEIGHT
#  define TEX_HEIGHT 64
# endif

//**map is map that extends with white spaces to make it rectangular
typedef struct s_map
{
	char	*north_path;
	char	*south_path;
	char	*west_path;
	char	*east_path;
	// int		floor_color;
	// int		ceiling_color;
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	char	**map;
	int		map_line_count;
	int		coloum_count;
	int		player_pos_x;
	int		player_pos_y;
	int		map_started_flag;
	int		map_index;
	int		map_end_flag;
	int		too_many_lines;
	int		found_player_flag;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_textures
{
	mlx_texture_t	*n_wall_texture;
	mlx_texture_t	*e_wall_texture;
	mlx_texture_t	*s_wall_texture;
	mlx_texture_t	*w_wall_texture;
	mlx_image_t		*n_wall_img;
	mlx_image_t		*e_wall_img;
	mlx_image_t		*s_wall_img;
	mlx_image_t		*w_wall_img;
	uint32_t		*pixels;
	int32_t			width;
	int32_t			height;
}	t_textures;

//ms = move speed
//db = distance buffer
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_map			*map;
	t_player		player;
	t_textures		*textures;
	int				tab_mode;
	int				skip_mouse_frame;
	double			last_mouse_x;
	mlx_image_t		*pause_text;
	mlx_image_t		*resume_text;
	mlx_image_t		*pause_overlay;
	uint32_t		x;
	uint32_t		y;
	double			ray_dir_x;
	double			ray_dir_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				map_x;
	int				map_y;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	uint32_t		draw_end;
	mlx_texture_t	*tex;
	double			wall_x;
	uint32_t		tex_x;
	uint32_t		tex_y;
	double			step;
	double			tex_pos;
	double			ms;
	double			db;
}	t_game;

//main
void	skip_spaces(char **map, int *i, int *j);
//src/parse_map
void	parse_map(const char *map_path, t_map *map);
void	missing_texture_exit(int fd, t_map *map, char **map_lines);
//src/parse_map/parse_map_helper.c
int		is_empty_line(char *line);
int		is_map_line(char *line);
int		texture_and_color_is_complete(t_map *map);
void	trim_newline(char *line);
void	too_many_lines_plz_clean(int fd, char **map_lines,
			t_map *map, char *line);
//src/parse_map/parse_map_helper2.c
int		one_of_the_dir(char *line);
void	get_lines_helper_helper(t_map *map, char *line, char **map_lines);
void	garbage_free(char *line, int fd, char **map_lines, t_map *map);
void	map_operation(char *line, int fd, char **map_lines, t_map *map);
//src/parse_map/save_map.c
void	save_map(t_map *map, char **map_lines);
//src/parse_map/save_color.c
void	save_color(t_map *map, char *line, int fd);
//src/parse_map/save_texture.c
void	dup_key_clean_up(int fd, t_map *map, char *line);
void	save_texture(t_map *map, char *line, int fd, char **map_lines);
//src/map_checker/map_checker.c
int		map_checker(t_map *map);
//src/map_checker/map_checker_helper.c
int		is_dup_player(t_map *map);
int		is_one_of_the_guy(t_map *map, int i, int j);
int		has_invalid_char(t_map *map);
int		invalid_get_out(t_map *map);
//utils.c
void	malloc_fail_exit(void);
void	free_matrix(char **matrix);
void	error_exit(char *reason);
void	free_lines_count(char **lines, int count);
void	print_matrix(char **matrix);
//game_init.c
void	exit_with_msg(char *msg);
void	game_init(t_game *game);
//player_init.c
void	init_player(t_game *game);
//render/render.c
void	render_map(t_game *game);
//render/render_helper.c
void	calculate_ray_direction(t_game *game, int w);
void	setup_dda(t_game *game, t_player *p);
void	perform_dda(t_game *game, t_map *map);
//src/handler/key_handler.c
void	handle_keypress(mlx_key_data_t keydata, void *param);
void	handle_input(void *param);
//src/handler/key_handler_helper.c
void	clear_image_by_put_pixel(mlx_image_t *img);
void	is_tab_mode(t_game *game);
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


void render_mini_map(t_game *game, t_map *map);
#endif
