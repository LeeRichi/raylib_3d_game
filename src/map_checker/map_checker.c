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
		return (error_print_return("Error\nSame color for f and c.\n"));
	if (is_dup_player(map))
		return (error_print_return("Error\nMore than one N in the map.\n"));
	if (has_invalid_char(map))
		return (error_print_return("Error\nInvalid character in map.\n"));
	if (!is_surroundings_valid(map))
		return (error_print_return("Error\nMap is not surrounded by walls.\n"));
	return (0);
}
