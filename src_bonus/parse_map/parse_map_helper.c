/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:31:31 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/09 23:28:05 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

int	is_empty_line(char *line)
{
	if (*line == '\n')
		return (1);
	return (0);
}

int	is_map_line(char *line)
{
	while (*line)
	{
		if (*line == '1')
			return (1);
		line++;
	}
	return (0);
}

int	texture_and_color_is_complete(t_map *map)
{
	if (map->north_path && map->south_path && map->west_path && map->east_path
		&& map->floor_color != 0 && map->ceiling_color != 0)
		return (1);
	return (0);
}

void	trim_newline(char *line)
{
	char	*newline_pos;

	newline_pos = ft_strchr(line, '\n');
	if (newline_pos)
		*newline_pos = '\0';
}

void	too_many_lines_plz_clean(int fd, char **map_lines,
	t_map *map)
{
	printf("Error: Too many lines in map\n");
	free_trims(map);
	close(fd);
	free_lines_count(map_lines, map->map_index);
	get_next_line(-1);
	exit(EXIT_FAILURE);
}
