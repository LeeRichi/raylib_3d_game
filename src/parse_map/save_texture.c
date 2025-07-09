/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:53:03 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/09 20:09:34 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	dup_key_clean_up(int fd, t_map *map, char *line)
{
	printf("Error\nKey can't not be duplicated.\n");
	free(line);
	close(fd);
	get_next_line(-1);
	free_trims(map);
	exit(EXIT_FAILURE);
}

void	save_texture_path(char **target_path, char *line, int fd, t_map *map)
{
	if (!*target_path)
		*target_path = ft_strtrim(line + 3, " \n");
	else
		dup_key_clean_up(fd, map, line);
	free(line);
}

void	save_texture(t_map *map, char *line, int fd, char **map_lines)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		free_lines_count(map_lines, map->map_index);
		save_texture_path(&map->north_path, line, fd, map);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		free_lines_count(map_lines, map->map_index);
		save_texture_path(&map->south_path, line, fd, map);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		free_lines_count(map_lines, map->map_index);
		save_texture_path(&map->west_path, line, fd, map);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		free_lines_count(map_lines, map->map_index);
		save_texture_path(&map->east_path, line, fd, map);
	}
	else
		free(line);
}
