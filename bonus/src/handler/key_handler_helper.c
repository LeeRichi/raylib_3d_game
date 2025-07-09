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

void	clear_image_by_put_pixel(mlx_image_t *img)
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

//toggle tab mode
void	is_tab_mode(t_game *game)
{
	static int	tab_pressed;

	tab_pressed = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_TAB))
	{
		if (!tab_pressed)
		{
			game->tab_mode = !game->tab_mode;
			tab_pressed = true;
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
	else
		tab_pressed = 0;
}
