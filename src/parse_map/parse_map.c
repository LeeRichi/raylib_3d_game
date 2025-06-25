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

void	local_free_print(char *line)
{
	printf("Warning: Unknown line: %s\n", line);
	free(line);
}

void	get_lines_helper(char *line, int fd, t_map *map, char **map_lines)
{
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			if (map->map_started_flag)
				map->map_end_flag = 1;
			free(line);
		}
		else if (one_of_the_dir(line))
			save_texture(map, line);
		else if (line[0] == 'F' || line[0] == 'C')
			save_color(map, line);
		else if (!map->map_started_flag && is_map_line(line))
			get_lines_helper_helper(map, line, map_lines);
		else if (map->map_started_flag && !map->map_end_flag)
			map_operation(line, fd, map_lines, map);
		else if (map->map_end_flag)
			garbage_free(line, fd, map_lines, map);
		else
			local_free_print(line);
		line = get_next_line(fd);
	}
}

void	missing_texture_exit(int fd, t_map *map, char **map_lines)
{
	printf("Error: Missing texture paths or color codes\n");
	close(fd);
	free_lines_count(map_lines, map->map_index);
	exit(EXIT_FAILURE);
}

void	parse_map(const char *map_path, t_map *map)
{
	int		fd;
	char	*line;
	char	*map_lines[MAX_LINES];

	line = NULL;
	map->map_started_flag = 0;
	map->map_index = 0;
	map->map_end_flag = 0;
	map->too_many_lines = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), exit(EXIT_FAILURE));
	get_lines_helper(line, fd, map, map_lines);
	if (!texture_and_color_is_complete(map))
		missing_texture_exit(fd, map, map_lines);
	map_lines[map->map_index] = NULL;
	save_map(map, map_lines);
	close(fd);
}
