/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:50:51 by chlee2            #+#    #+#             */
/*   Updated: 2025/06/27 21:58:29 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_rgb_valid(char **rgb)
{
	int	i;
	int	value;

	i = 0;
	while (rgb[i])
	{
		if (!is_valid_number(rgb[i]))
			return (0);
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
			return (0);
		i++;
	}
	return (i == 3);
}

////ABGR
static void	translate_color(t_map *map, char *line, char *which)
{
	char	**rgb;
	char	*trim;

	trim = ft_strtrim(line + 1, " \t\n");
	rgb = ft_split(trim, ',');
	free(trim);
	printf("0: %s	1: %s	2: %s	3: %s\n", rgb[0],rgb[1],rgb[2],rgb[3]);
	if (!rgb[0] || !rgb[1] || !rgb[2] || !is_rgb_valid(rgb))
	{
		free_matrix(rgb);
		error_exit("Invalid color format");
	}
	if (ft_strcmp(which, "F") == 0)
	{
		map->floor_color = (255 << 24 | ft_atoi(rgb[2]) << 16)
			| (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[0]);
			printf("floor color: %i	in uint32: %u\n", map->floor_color, (uint32_t) map->floor_color);
	}
	else if (ft_strcmp(which, "C") == 0)
	{
		map->ceiling_color = (255 << 24 | ft_atoi(rgb[2]) << 16)
			| (ft_atoi(rgb[1]) << 8) | ft_atoi(rgb[0]);
			printf("ceiling color: %i	in uint32: %u\n", map->ceiling_color, (uint32_t) map->ceiling_color);
	}
	free_matrix(rgb);
}

void	save_color(t_map *map, char *line, int fd)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (!map->floor_color)
			translate_color(map, line, "F");
		else
			dup_key_clean_up(fd, map, line);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (!map->ceiling_color)
			translate_color(map, line, "C");
		else
			dup_key_clean_up(fd, map, line);
	}
	free(line);
}
