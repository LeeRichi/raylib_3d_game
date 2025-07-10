/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:48:40 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/11 00:45:37 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D_bonus.h"

static void	free_map_lines(char **map_lines)
{
	int	i;

	i = 0;
	while (map_lines[i])
	{
		free(map_lines[i]);
		i++;
	}
}

void	save_map_helper(t_map *map, size_t max_len, char **map_lines)
{
	int		i;
	size_t	len;

	i = 0;
	while (i < map->map_line_count)
	{
		len = ft_strlen(map_lines[i]);
		map->map[i] = malloc(max_len + 1);
		if (!map->map[i])
		{
			while (--i >= 0)
				free(map->map[i]);
			free(map->map);
			free_map_lines(map_lines);
			free_trims(map);
			malloc_fail_exit();
		}
		ft_memcpy(map->map[i], map_lines[i], len);
		ft_memset(map->map[i] + len, ' ', max_len - len);
		map->map[i][max_len] = '\0';
		free(map_lines[i]);
		i++;
	}
	map->map[i] = NULL;
}

void	save_map(t_map *map, char **map_lines)
{
	int		i;
	size_t	max_len;
	size_t	len;

	map->map_line_count = 0;
	while (map_lines[map->map_line_count])
		map->map_line_count++;
	max_len = 0;
	i = 0;
	while (i < map->map_line_count)
	{
		len = ft_strlen(map_lines[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	map->coloum_count = max_len;
	map->map = malloc(sizeof(char *) * (map->map_line_count + 1));
	if (!map->map)
	{
		free_trims(map);
		free_map_lines(map_lines);
		malloc_fail_exit();
	}
	save_map_helper(map, max_len, map_lines);
}
