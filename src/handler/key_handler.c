/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:48:56 by chlee2            #+#    #+#             */
/*   Updated: 2025/06/15 17:01:43 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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

	// Clear the image before drawing
	clear_image(game->img);

	// if (mlx_is_key_down(mlx, MLX_KEY_TAB))
	// {
	// 	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	// }

	// Move forward
	if (mlx_is_key_down(mlx, MLX_KEY_W)	|| mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		if (game->map->map[(int)(p->y)][(int)(p->x + p->dir_x * move_speed)] != '1')
			p->x += p->dir_x * move_speed;
		if (game->map->map[(int)(p->y + p->dir_y * move_speed)][(int)(p->x)] != '1')
			p->y += p->dir_y * move_speed;
	}

	// Move backward
	if (mlx_is_key_down(mlx, MLX_KEY_S) || mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		if (game->map->map[(int)(p->y)][(int)(p->x - p->dir_x * move_speed)] != '1')
			p->x -= p->dir_x * move_speed;
		if (game->map->map[(int)(p->y - p->dir_y * move_speed)][(int)(p->x)] != '1')
			p->y -= p->dir_y * move_speed;
	}

	// Move right
	if (mlx_is_key_down(mlx, MLX_KEY_A) || mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		if (game->map->map[(int)(p->y)][(int)(p->x - p->plane_x * move_speed)] != '1')
			p->x -= p->plane_x * move_speed;
		if (game->map->map[(int)(p->y - p->plane_y * move_speed)][(int)(p->x)] != '1')
			p->y -= p->plane_y * move_speed;
	}

	// Move left
	if (mlx_is_key_down(mlx, MLX_KEY_D) || mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		if (game->map->map[(int)(p->y)][(int)(p->x + p->plane_x * move_speed)] != '1')
			p->x += p->plane_x * move_speed;
		if (game->map->map[(int)(p->y + p->plane_y * move_speed)][(int)(p->x)] != '1')
			p->y += p->plane_y * move_speed;
	}

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		//free?
		return;
	}

	// update_jump(game, 1);       // ✅ ← Add it here

	// Draw the new frame
	render_map(game);
}
