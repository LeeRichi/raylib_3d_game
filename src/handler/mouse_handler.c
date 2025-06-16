/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:49:09 by chlee2            #+#    #+#             */
/*   Updated: 2025/06/15 23:41:39 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


void handle_mouse_move(double xpos, double ypos, void *param)
{
	(void)ypos;

	t_game *game = (t_game *)param;

	if (game->tab_mode)
	{
		return;
	}
	double sensitivity = 0.001;

	if (game->skip_mouse_frame)
	{
		game->skip_mouse_frame = 0;
		game->last_mouse_x = xpos;  // Reset last_mouse_x here to current xpos
		return;
	}

	double delta_x = xpos - game->last_mouse_x;

	game->last_mouse_x = xpos;

	double rot = -delta_x * sensitivity;

	double old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rot) - game->player.dir_y * sin(-rot);
	game->player.dir_y = old_dir_x * sin(-rot) + game->player.dir_y * cos(-rot);

	double old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rot) - game->player.plane_y * sin(-rot);
	game->player.plane_y = old_plane_x * sin(-rot) + game->player.plane_y * cos(-rot);
}
