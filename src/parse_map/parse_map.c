/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:31:31 by chlee2            #+#    #+#             */
/*   Updated: 2025/05/13 11:54:31 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

//later change things to static if not used in other files

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
	if (map->north_path && map->south_path && map->west_path && map->east_path)
		return (1);
	if (map->floor_color != -1 && map->ceiling_color != -1)
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

void	parse_map(const char *map_path, t_map *map)
{
	int fd;
	char	*line = NULL;
	char	*map_lines[MAX_LINES];
	int		map_started_flag = 0;
	int		map_index = 0;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (perror("open"), exit(EXIT_FAILURE));
	while ((line = get_next_line(fd)))
	{
		if (is_empty_line(line))
			free(line);
		else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
				ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
				{
					save_texture(map, line);
					free(line);
				}
		else if (line[0] == 'F' || line[0] == 'C')
		{
			save_color(map, line);
			free(line);
		}
		else if (!map_started_flag && is_map_line(line))
		{
			map_started_flag = 1;
			trim_newline(line);
			map_lines[map_index++] = line;
		}
		else if (map_started_flag)
		{
			trim_newline(line);
			map_lines[map_index++] = line;
		}
		else
			printf("Warning: Unknown line: %s\n", line), free(line); //get back later, for now it is just empty lines //might not need this line
		if (map_index >= MAX_LINES)
		{
			printf("Error: Too many lines in map\n");
			close(fd);
			free_lines_count(map_lines, map_index);
			exit(EXIT_FAILURE);
		}
	}
	if (!texture_and_color_is_complete(map))
	{
		printf("Error: Missing texture paths or color codes\n");
		close(fd);
		free_lines_count(map_lines, map_index);
		exit(EXIT_FAILURE);
	}
	map_lines[map_index] = NULL;
	save_map(map, map_lines);
	close(fd);
}


