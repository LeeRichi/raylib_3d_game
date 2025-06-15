/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:49:09 by chlee2            #+#    #+#             */
/*   Updated: 2025/06/15 16:49:35 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void handle_mouse_move(double xpos, double ypos, void *param)
{
	(void)ypos;
	t_game *game = (t_game *)param;
	static double last_x = 960;
	double sensitivity = 0.001;
	double delta_x = xpos - last_x;

	last_x = xpos;

	double rot = -delta_x * sensitivity;

	double old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rot) - game->player.dir_y * sin(-rot);
	game->player.dir_y = old_dir_x * sin(-rot) + game->player.dir_y * cos(-rot);

	double old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rot) - game->player.plane_y * sin(-rot);
	game->player.plane_y = old_plane_x * sin(-rot) + game->player.plane_y * cos(-rot);
}
