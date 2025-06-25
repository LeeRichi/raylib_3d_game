/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:38:08 by chlee2            #+#    #+#             */
/*   Updated: 2025/05/18 16:02:56 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int has_invalid_char_helper(t_map *map, int i, int j, int *found_player_flag)
{
	if (*found_player_flag)
	{
		printf("Error\nFound more than 1 player\n");
		return (1);
	}
	map->player_pos_x = j;
	map->player_pos_y = i;
	*found_player_flag = 1;
	return (0);
}

int	has_invalid_char(t_map *map)
{
	int	i;
	int	j;
	int	found_player_flag;

	found_player_flag = 0;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			while (map->map[i][j] == ' ' || map->map[i][j] == '\t'
				|| map->map[i][j] == '\r'
				|| map->map[i][j] == '\v' || map->map[i][j] == '\f')
					j++;
			if (map->map[i][j] == '\0')
				break;
			if (map->map[i][j] == 'N')
			{
				if (has_invalid_char_helper(map, i, j, &found_player_flag))
					return (1);
			}
			if (map->map[i][j] != '1' && map->map[i][j] != '0' && map->map[i][j] != 'N'
				&& map->map[i][j] != 'S' && map->map[i][j] != 'E' && map->map[i][j] != 'W' && map->map[i][j] != '\0')
			{
				printf("Error\nInvalid character in map: %c\n", map->map[i][j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	invalid_get_out(t_map *map)
{
	int	j;

	j = 0;
	while (map->map[0][j])
	{
		if (map->map[0][j] != '1' && map->map[0][j] != ' ')
			return (0);
		j++;
	}
	j = 0;
	while (map->map[map->map_line_count - 1][j])
	{
		if (map->map[map->map_line_count - 1][j] != '1' &&
			map->map[map->map_line_count - 1][j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

int	is_surroundings_valid(t_map *map)
{
	int	i;
	int	j;
	int	len;

	if (!invalid_get_out(map))
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

int	is_valid_color(int color)
{
	if (color < 0 || color > 0xFFFFFF)
	{
		printf("Error\nInvalid color value.\n");
		return (0);
	}
	return (1);
}

int	map_checker(t_map *map)
{
	if (!is_valid_color(map->floor_color))
	{
		printf("Error\nInvalid floor color.\n");
		return (1);
	}
	if (map->floor_color == map->ceiling_color)
	{
		printf("Error\nFloor and ceiling colors cannot be the same.\n");
		return (1);
	}
	if (has_invalid_char(map))
	{
		printf("Error\nInvalid character in map.\n");
		return (1);
	}
	if (!is_surroundings_valid(map))
	{
		printf("Error\nMap is not surrounded by walls.\n");
		return (1);
	}
	return (0);
}
