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

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
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
		&& map->floor_color != -1 && map->ceiling_color != -1)
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

void too_many_lines_plz_clean(int fd, char **map_lines, t_map *map)
{
	printf("Error: Too many lines in map\n");
	close(fd);
	free_lines_count(map_lines, map->map_index);
	exit(EXIT_FAILURE);
}

int one_of_the_dir(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			return (1);
	return (0);
}

void get_lines_helper_helper(t_map *map, char *line, char **map_lines)
{
	map->map_started_flag = 1;
	trim_newline(line);
	map_lines[map->map_index++] = line;
}

void	get_lines_helper(char *line, int fd, t_map *map, char **map_lines)
{
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			if (map->map_started_flag)
				break ;
		}
		else if (one_of_the_dir(line))
			save_texture(map, line);
		else if (line[0] == 'F' || line[0] == 'C')
			save_color(map, line);
		else if (!map->map_started_flag && is_map_line(line))
			get_lines_helper_helper(map, line, map_lines);
		// {
		// 	map->map_started_flag = 1;
		// 	trim_newline(line);
		// 	map_lines[map->map_index++] = line;
		// }
		else if (map->map_started_flag)
		{
			trim_newline(line);
			map_lines[map->map_index++] = line;
		}
		else
			printf("Warning: Unknown line: %s\n", line), free(line);
		if (map->map_index >= MAX_LINES)
			too_many_lines_plz_clean(fd, map_lines, map);
		line = get_next_line(fd);
	}
}

void	parse_map(const char *map_path, t_map *map)
{
	int		fd;
	char	*line = NULL;
	char	*map_lines[MAX_LINES];

	map->map_started_flag = 0;
	map->map_index = 0;
	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), exit(EXIT_FAILURE));

	get_lines_helper(line, fd, map, map_lines);

	if (!texture_and_color_is_complete(map))
	{
		printf("Error: Missing texture paths or color codes\n");
		close(fd);
		free_lines_count(map_lines, map->map_index);
		exit(EXIT_FAILURE);
	}
	map_lines[map->map_index] = NULL;
	save_map(map, map_lines);
	while (line)
	{
		if (!is_empty_line(line))
		{
			printf("Error: Garbage line after map ends: %s\n", line);
			free(line);
			close(fd);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
