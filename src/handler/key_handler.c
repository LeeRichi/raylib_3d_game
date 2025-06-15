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
            mlx_put_pixel(img, x, y, 0x000000FF);
}

void render_pause_screen(t_game *game, int show)
{
    if (show)
    {
        if (!game->pause_text)
            game->pause_text = mlx_put_string(game->mlx, "PAUSED", 20, 20);
        if (!game->resume_text)
            game->resume_text = mlx_put_string(game->mlx, "Press TAB to resume", 20, 50);
    }
    else
    {
        if (game->pause_text)
        {
            mlx_delete_image(game->mlx, game->pause_text);
            game->pause_text = NULL;
        }
        if (game->resume_text)
        {
            mlx_delete_image(game->mlx, game->resume_text);
            game->resume_text = NULL;
        }
    }
}

void is_tab_mode(t_game *game)
{
	bool tab_pressed_last_frame = false;

	if (mlx_is_key_down(game->mlx, MLX_KEY_TAB))
	{
		if (!tab_pressed_last_frame)
		{
			game->tab_mode = !game->tab_mode;

			if (game->tab_mode)
			{
				mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);  // show cursor
				render_pause_screen(game, 1);
			}
			else
			{
				mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED); // lock/hide
				// Optional: recenter to prevent snap
				// mlx_set_mouse_pos(game->mlx, 1920 / 2, 1080 / 2);
				game->skip_mouse_frame = 1;  // <- skip mouse delta after re-lock
				render_pause_screen(game, 0);

			}
		}
		tab_pressed_last_frame = true;
	}
	else
		tab_pressed_last_frame = false;
}

void	handle_input(void *param)
{
	t_game	*game = (t_game *)param;
	t_player	*p = &game->player;
	mlx_t	*mlx = game->mlx;
	double	move_speed = 0.05;

	clear_image(game->img);

	is_tab_mode(game);

	if (game->tab_mode)
	{
		render_pause_screen(game, 1);
		return;
	}

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

	// Draw the new frame
	render_map(game);
}
