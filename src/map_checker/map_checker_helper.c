/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:38:08 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/01 22:03:33 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_dup_player(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->found_player_flag = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			skip_spaces(map->map, &i, &j);
			if (map->map[i][j] == '\0')
				break ;
			if (ft_strchr("NEWS", map->map[i][j]))//changed this line to check dupication for all players.
			{
				if (map->found_player_flag == 1)
					return (1);
				map->found_player_flag = 1;
			}
			j++;
		}
		i++;
	}
	return (!map->found_player_flag);//this will return 0 if the player is found. if none found 1. There was no room for two lines to add if condition followed by return.
}

int	is_one_of_the_guy(t_map *map, int i, int j)
{
	if (map->map[i][j] != '1' && map->map[i][j] != '0' && map->map[i][j] != 'N'
		&& map->map[i][j] != 'S' && map->map[i][j] != 'E'
		&& map->map[i][j] != 'W' && map->map[i][j] != '\0')
		return (1);
	return (0);
}

int	has_invalid_char(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			skip_spaces(map->map, &i, &j);
			if (map->map[i][j] == '\0')
				break ;
			else if (is_one_of_the_guy(map, i, j))
				return (1);
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
