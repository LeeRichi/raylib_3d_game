/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 16:46:07 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/09 22:02:22 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	compute_wall_projection(t_game *game)
{
	if (game->side == 0)
		game->perp_wall_dist = (game->side_dist_x - game->delta_dist_x);
	else
		game->perp_wall_dist = game->side_dist_y - game->delta_dist_y;
	if (game->perp_wall_dist < 1e-6)
		game->perp_wall_dist = 1e-6;
	game->line_height = (int)(game->img->height / game->perp_wall_dist);
	game->draw_start = -(game->line_height) / 2 + game->img->height / 2;
	game->draw_end = game->line_height / 2 + game->img->height / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	if (game->draw_end >= game->img->height)
		game->draw_end = game->img->height - 1;
	if (game->side == 0 && game->ray_dir_x < 0)
		game->tex = game->textures->w_wall_texture;
	else if (game->side == 0 && game->ray_dir_x >= 0)
		game->tex = game->textures->e_wall_texture;
	else if (game->side == 1 && game->ray_dir_y < 0)
		game->tex = game->textures->n_wall_texture;
	else
		game->tex = game->textures->s_wall_texture;
}

void	texture_mapping(t_game *game, t_player *p)
{
	if (game->side == 0)
		game->wall_x = p->y + game->perp_wall_dist * game->ray_dir_y;
	else
		game->wall_x = p->x + game->perp_wall_dist * game->ray_dir_x;
	game->wall_x -= floor(game->wall_x);
	game->tex_x = (int)(game->wall_x * (double)(game->tex->width));
	if (game->tex_x < 0)
		game->tex_x = 0;
	if (game->tex_x >= game->tex->width)
		game->tex_x = game->tex->width - 1;
	if ((game->side == 0 && game->ray_dir_x < 0)
		|| (game->side == 1 && game->ray_dir_y > 0))
		game->tex_x = game->tex->width - game->tex_x - 1;
}

void	draw_each_col(t_game *game)
{
	int			i;
	uint32_t	color;

	game->step = (double)game->tex->height / game->line_height;
	game->tex_pos = (game->draw_start - game->img->height / 2
			+ game->line_height / 2) * game->step;
	game->y = game->draw_start;
	while (game->y < game->draw_end)
	{
		game->tex_y = fmin(fmax((int)game->tex_pos, 0), game->tex->height - 1);
		game->tex_pos += game->step;
		i = (game->tex_y * game->tex->width + game->tex_x) * 4;
		color = (game->tex->pixels[i] << 24)
			| (game->tex->pixels[i + 1] << 16)
			| (game->tex->pixels[i + 2] << 8)
			| (game->tex->pixels[i + 3]);
		mlx_put_pixel(game->img, game->x, game->y, color);
		game->y++;
	}
}

void	render_ceiling_and_floor(t_game *game)
{
	uint32_t	*pixels;
	uint32_t	color;
	int			y;
	int			x;

	pixels = (uint32_t *)game->img->pixels;
	y = 0;
	while (y < (int)game->img->height)
	{
		if (y < (int)game->img->height / 2)
			color = game->map->ceiling_color;
		else
			color = game->map->floor_color;
		x = 0;
		while (x < (int)game->img->width)
		{
			pixels[y * (int)game->img->width + x] = color;
			x++;
		}
		y++;
	}
}

void	render_map(t_game *game)
{
	t_player	*p;
	t_map		*map;

	p = &game->player;
	map = game->map;
	render_ceiling_and_floor(game);
	game->x = 0;
	while (game->x < game->img->width)
	{
		calculate_ray_direction(game, game->img->width);
		setup_dda(game, p);
		perform_dda(game, map);
		compute_wall_projection(game);
		texture_mapping(game, p);
		draw_each_col(game);
		game->x++;
	}
}
