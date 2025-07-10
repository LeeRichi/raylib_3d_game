/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:48:56 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/10 20:05:14 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

void	try_move_player(t_game *game, t_player *p, double move_x, double move_y)
{
	if (game->map->map[(int)(p->y)][(int)(p->x + move_x
			* (game->ms + game->db))] != '1')
		p->x += move_x * game->ms;
	if (game->map->map[(int)(p->y + move_y
			* (game->ms + game->db))][(int)(p->x)] != '1')
		p->y += move_y * game->ms;
}

void	rotate_player(t_player *p, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

void	key_right_left(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(&game->player, -(game->ms));
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(&game->player, game->ms);
}

void	handle_keypress(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_TAB)
	{
		is_tab_mode(keydata, game);
	}
}

void	handle_input(void *param)
{
	t_game		*game;
	t_player	*p;

	game = (t_game *)param;
	p = &game->player;
	game->ms = 0.05;
	game->db = 0.08;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		try_move_player(game, p, p->dir_x, p->dir_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		try_move_player(game, p, -p->dir_x, -p->dir_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		try_move_player(game, p, -p->plane_x, -p->plane_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		try_move_player(game, p, p->plane_x, p->plane_y);
	key_right_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		return ;
	}
	render_map(game);
}
