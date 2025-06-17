/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:48:56 by chlee2            #+#    #+#             */
/*   Updated: 2025/06/15 23:39:55 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


void clear_image_by_put_pixel(mlx_image_t *img)
{
	int	w;
    int	h;
	int	x;
	int	y;
	
	w = img->width;
	h = img->height;
	
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			mlx_put_pixel(img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

// void clear_pause_overlay(t_game *game)
// {
// 	if (game->pause_text)
// 	{
// 		mlx_delete_image(game->mlx, game->pause_text);
// 		game->pause_text = NULL;
// 	}
// 	if (game->resume_text)
// 	{
// 		mlx_delete_image(game->mlx, game->resume_text);
// 		game->resume_text = NULL;
// 	}
// }

// void render_pause_screen(t_game *game, int show)
// {
// 	if (show)
// 	{
// 		if (!game->pause_text)
// 			game->pause_text = mlx_put_string(game->mlx, "PAUSED", 20, 20);
// 		if (!game->resume_text)
// 			game->resume_text = mlx_put_string(game->mlx, "Press TAB to resume", 20, 50);
// 		if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
// 		{
// 			mlx_close_window(game->mlx);
// 			return;
// 		}
// 	}
// 	else
// 		clear_pause_overlay(game);
// }

//toggle tab mode
void is_tab_mode(t_game *game)
{

	if (mlx_is_key_down(game->mlx, MLX_KEY_TAB))
	{
		game->tab_mode = !game->tab_mode;

		if (game->tab_mode)
		{
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
			render_pause_screen(game, 1);
		}
		else
		{
			mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
			game->skip_mouse_frame = 1;
			render_pause_screen(game, 0);
		}
	}
}

//draw 
void	handle_input(void *param)
{
	t_game	*game = (t_game *)param;
	t_player	*p = &game->player;
	mlx_t	*mlx = game->mlx;
	double	move_speed = 0.05;
	double rot;

	clear_image_by_put_pixel(game->img);

	is_tab_mode(game);

	if (game->tab_mode)
	{
		render_pause_screen(game, 1);
		return;
	}

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

	// Move right
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (game->map->map[(int)(p->y)][(int)(p->x - p->plane_x * move_speed)] != '1')
			p->x -= p->plane_x * move_speed;
		if (game->map->map[(int)(p->y - p->plane_y * move_speed)][(int)(p->x)] != '1')
			p->y -= p->plane_y * move_speed;
	}

	// Move left
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		if (game->map->map[(int)(p->y)][(int)(p->x + p->plane_x * move_speed)] != '1')
			p->x += p->plane_x * move_speed;
		if (game->map->map[(int)(p->y + p->plane_y * move_speed)][(int)(p->x)] != '1')
			p->y += p->plane_y * move_speed;
	}

	// double buffer = 0.1;

	// // Move forward
	// if (mlx_is_key_down(mlx, MLX_KEY_W))
	// {
	// 	// if (game->map->map[(int)(p->y)][(int)(p->x + p->dir_x * move_speed)] != '1')
	// 	// 	p->x += p->dir_x * move_speed;
	// 	// if (game->map->map[(int)(p->y + p->dir_y * move_speed)][(int)(p->x)] != '1')
	// 	// 	p->y += p->dir_y * move_speed;
	// 	if (game->map->map[(int)(p->y)][(int)(p->x + p->dir_x * (move_speed + buffer))] != '1')
	// 		p->x += p->dir_x * move_speed;
	// 	if (game->map->map[(int)(p->y + p->dir_y * (move_speed + buffer))][(int)(p->x)] != '1')
	// 		p->y += p->dir_y * move_speed;
	// }

	// // Move backward (S)
	// if (mlx_is_key_down(mlx, MLX_KEY_S))
	// {
	// 	if (game->map->map[(int)(p->y)][(int)(p->x - p->dir_x * (move_speed + buffer))] != '1')
	// 		p->x -= p->dir_x * move_speed;
	// 	if (game->map->map[(int)(p->y - p->dir_y * (move_speed + buffer))][(int)(p->x)] != '1')
	// 		p->y -= p->dir_y * move_speed;
	// }

	// // Move left (A) — strafe left
	// if (mlx_is_key_down(mlx, MLX_KEY_A))
	// {
	// 	if (game->map->map[(int)(p->y)][(int)(p->x - p->plane_x * (move_speed + buffer))] != '1')
	// 		p->x -= p->plane_x * move_speed;
	// 	if (game->map->map[(int)(p->y - p->plane_y * (move_speed + buffer))][(int)(p->x)] != '1')
	// 		p->y -= p->plane_y * move_speed;
	// }

	// // Move right (D) — strafe right
	// if (mlx_is_key_down(mlx, MLX_KEY_D))
	// {
	// 	if (game->map->map[(int)(p->y)][(int)(p->x + p->plane_x * (move_speed + buffer))] != '1')
	// 		p->x += p->plane_x * move_speed;
	// 	if (game->map->map[(int)(p->y + p->plane_y * (move_speed + buffer))][(int)(p->x)] != '1')
	// 		p->y += p->plane_y * move_speed;
	// }

	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		rot = -move_speed;

		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rot) - game->player.dir_y * sin(-rot);
		game->player.dir_y = old_dir_x * sin(-rot) + game->player.dir_y * cos(-rot);

		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rot) - game->player.plane_y * sin(-rot);
		game->player.plane_y = old_plane_x * sin(-rot) + game->player.plane_y * cos(-rot);
	}

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		rot = move_speed;

		double old_dir_x = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rot) - game->player.dir_y * sin(-rot);
		game->player.dir_y = old_dir_x * sin(-rot) + game->player.dir_y * cos(-rot);

		double old_plane_x = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rot) - game->player.plane_y * sin(-rot);
		game->player.plane_y = old_plane_x * sin(-rot) + game->player.plane_y * cos(-rot);
	}


	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		return;
	}

	render_map(game);
}
