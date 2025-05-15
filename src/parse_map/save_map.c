/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:48:40 by chlee2            #+#    #+#             */
/*   Updated: 2025/05/15 14:51:14 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	save_map(t_map *map, char **map_lines)
{
	int		i;
	size_t	max_len;

	map->map_line_count = 0;
	while (map_lines[map->map_line_count])
		map->map_line_count++;
	max_len = 0;
	i = 0;
	while (i < map->map_line_count)
	{
		size_t len = ft_strlen(map_lines[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	map->coloum_count = max_len;
	map->map = malloc(sizeof(char *) * (map->map_line_count + 1));
	if (!map->map)
		malloc_fail_exit();
	i = 0;
	while (i < map->map_line_count)
	{
		size_t len = ft_strlen(map_lines[i]);
		map->map[i] = malloc(max_len + 1);
		if (!map->map[i])
		{
			while (--i >= 0)
				free(map->map[i]);
			free(map->map);
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
