/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:31:31 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/09 23:28:10 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

void	get_lines_helper(char *line, int fd, t_map *map, char **map_lines)
{
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line) && map->map_started_flag)
		{
			if (map->map_started_flag)
				map->map_end_flag = 1;
			free(line);
		}
		else if (is_empty_line(line))
			free(line);
		else if (one_of_the_dir(line) && !map->map_started_flag)
			save_texture(map, line, fd, map_lines);
		else if ((line[0] == 'F' || line[0] == 'C') && !map->map_started_flag)
			save_color(map, line, fd);
		else if (!map->map_started_flag && is_map_line(line)
			&& !map->map_end_flag)
			map_operation(line, fd, map_lines, map);
		else if (map->map_started_flag && !map->map_end_flag)
			map_operation(line, fd, map_lines, map);
		else if (ft_strcmp(line, "\n") != 0)
			garbage_free(line, fd, map_lines, map);
		line = get_next_line(fd);
	}
}

void	missing_texture_exit(int fd, t_map *map, char **map_lines)
{
	printf("Error: Missing texture paths or color codes\n");
	close(fd);
	free_lines_count(map_lines, map->map_index);
	get_next_line(-1);
	free_trims(map);
	exit(EXIT_FAILURE);
}

void	parse_map(const char *map_path, t_map *map)
{
	int		fd;
	char	*line;
	char	*map_lines[MAX_LINES];

	line = NULL;
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
