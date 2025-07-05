/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:38:08 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/05 13:36:11 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_point get_player_pos(t_map *map)
{
	t_point	player_pos;

	player_pos.x = -1;
	player_pos.y = -1;
	if (map->found_player_flag == 0)
		return (player_pos);
	for (int i = 0; map->map[i]; i++)
	{
		for (int j = 0; map->map[i][j]; j++)
		{
			skip_spaces(map->map, &i, &j);
			if (map->map[i][j] == '\0')
    			continue;
			if (ft_strchr("NEWS", map->map[i][j]))
			{
				player_pos.x = j;
				player_pos.y = i;
				return (player_pos);
			}
		}
	}
	return (player_pos);
}

int	check_leak(char **map, t_point sz)
{
	for (int x = 0; x < sz.x; x++)
	{
		if (map[0][x] == 'F' || map[sz.y - 1][x] == 'F')
			return (1);
	}
	for (int y = 0; y < sz.y; y++)
	{
		if (map[y][0] == 'F' || map[y][sz.x - 1] == 'F')
			return (1);
	}
	return (0);
}

int	copy_map_line(t_map *map, char **temp)
{
	int i, j;

	if (!map || !temp)
		return (1);
	i = 0;
	while (i < map->map_line_count)
	{
		temp[i] = malloc(sizeof(char) * (map->coloum_count + 1));
		if (!temp[i])
		{
			j = 0;
			while (j < i)
				free(temp[j++]);
			return (1);
		}
		ft_strlcpy(temp[i], map->map[i], map->coloum_count + 1);
		i++;
	}
	return (0);
}

int	flood_fill_checker(t_map *map)
{
	char **temp;
	int i;

	temp = malloc(sizeof(char *) * (map->map_line_count + 1));
	if (!temp)
		return (1);
	if (copy_map_line(map, temp))
	{
		free(temp);
		return (1);
	}
	rich_flood_fill(temp, (t_point){map->coloum_count, map->map_line_count}, get_player_pos(map));
	if (check_leak(temp, (t_point){map->coloum_count, map->map_line_count}))
	{
		i = 0;
		while (i < map->map_line_count)
		{
			free(temp[i]);
			i++;
		}
		free(temp);
		return (1);
	}
	return (0);
}

int	is_surroundings_valid(t_map *map)
{
	int	i;
	int	j;
	int	len;

	if (!invalid_get_out(map) || flood_fill_checker(map))
		return (0);
	i = 1;
	while (i < map->map_line_count - 1)
	{
		j = 0;
		skip_spaces(map->map, &i, &j);
		if (map->map[i][j] != '1')
			return (0);
		len = ft_strlen(map->map[i]) - 1;
		while (len > 0 && map->map[i][len] == ' ')
			len--;
		if (map->map[i][len] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_color(uint32_t color)
{
	if (color < 0 || color > 0xFFFFFF)
	{
		printf("Error\nInvalid color value.\n");
		return (0);
	}
	return (1);
}

static int	error_print_return(char *msg)
{
	printf("%s", msg);
	return (1);
}

int	map_checker(t_map *map)
{
	// if (!is_valid_color(map->floor_color) && !is_valid_color(map->ceiling_color))
	// 	return (error_print_return("Error\nInvalid floor color.\n"));
	if (map->floor_color == map->ceiling_color)
		return (error_print_return("Error\nSame color for floor and ceiling.\n"));
	if (is_dup_player(map))
		return (error_print_return("Error\nMore than one or none player start positions found in the map.\n"));
	if (has_invalid_char(map))
		return (error_print_return("Error\nInvalid character in map.\n"));
	if (!is_surroundings_valid(map))
		return (error_print_return("Error\nMap is not surrounded by walls.\n"));
	return (0);
}
