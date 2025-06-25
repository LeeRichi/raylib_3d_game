/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:31:31 by chlee2            #+#    #+#             */
/*   Updated: 2025/05/15 14:31:23 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	one_of_the_dir(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	return (0);
}

void	get_lines_helper_helper(t_map *map, char *line, char **map_lines)
{
	map->map_started_flag = 1;
	trim_newline(line);
	map_lines[map->map_index++] = line;
}

void	garbage_free(char *line, int fd, char **map_lines, t_map *map)
{
	printf("Garbage line detected: %s\n", line);
	free(line);
	close(fd);
	free_lines_count(map_lines, map->map_index);
	free_trims(map);
	exit(EXIT_FAILURE);
}

void	map_operation(char *line, int fd, char **map_lines, t_map *map)
{
	if (ft_strlen(line) >= MAX_LINES)
	{
		free(line);
		too_many_lines_plz_clean(fd, map_lines, map, line);
	}
	trim_newline(line);
	map_lines[map->map_index++] = line;
	if (map->map_index >= MAX_LINES)
		too_many_lines_plz_clean(fd, map_lines, map, line);
}
