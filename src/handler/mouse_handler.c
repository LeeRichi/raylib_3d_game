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

void	handle_mouse_move_helper(double xpos, double sensitivity, t_game *game)
{
	double	delta_x;
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	delta_x = xpos - game->last_mouse_x;
	game->last_mouse_x = xpos;
	rot = -delta_x * sensitivity;
	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rot) - game->player.dir_y
		* sin(-rot);
	game->player.dir_y = old_dir_x * sin(-rot) + game->player.dir_y
		* cos(-rot);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x
		* cos(-rot) - game->player.plane_y * sin(-rot);
	game->player.plane_y = old_plane_x
		* sin(-rot) + game->player.plane_y * cos(-rot);
}

void	handle_mouse_move(double xpos, double ypos, void *param)
{
	t_game	*game;
	double	sensitivity;

	(void)ypos;
	game = (t_game *)param;
	if (game->tab_mode)
		return ;
	sensitivity = 0.001;
	if (game->skip_mouse_frame)
	{
		game->skip_mouse_frame = 0;
		game->last_mouse_x = xpos;
		return ;
	}
	handle_mouse_move_helper(xpos, sensitivity, game);
}
