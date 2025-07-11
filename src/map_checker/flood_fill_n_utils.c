/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_n_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 18:31:13 by wweerasi          #+#    #+#             */
/*   Updated: 2025/07/11 00:49:37 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

t_point	get_player_pos(t_map *map)
{
	t_point	player_pos;
	int		i;
	int		j;

	player_pos.x = -1;
	player_pos.y = -1;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			skip_spaces(map->map, &i, &j);
			if (map->map[i][j] == '\0')
				break ;
			if (ft_strchr("NEWS", map->map[i][j]))
			{
				assign_values_for_get_player_pos(i, j, &player_pos);
				return (player_pos);
			}
			j++;
		}
		i++;
	}
	return (player_pos);
}

int	check_leak(char **map, t_point sz)
{
	int	x;
	int	y;

	x = 0;
	while (x < sz.x)
	{
		if (map[0][x] == 'F' || map[sz.y - 1][x] == 'F')
			return (1);
		x++;
	}
	y = 0;
	while (y < sz.y)
	{
		if (map[y][0] == 'F' || map[y][sz.x - 1] == 'F')
			return (1);
		y++;
	}
	return (0);
}

int	copy_map_line(t_map *map, char **temp)
{
	int	i;
	int	j;

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
			free(temp);
			return (1);
		}
		ft_strlcpy(temp[i], map->map[i], map->coloum_count + 1);
		i++;
	}
	temp[i] = NULL;
	return (0);
}

static int	free_temp_map(char **temp, int line_count, int exit_code)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(temp[i]);
		i++;
	}
	free(temp);
	return (exit_code);
}

int find_zeros(t_point *zero, char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				zero->y = i;
				zero->x = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	flood_fill_checker(t_map *map)
{
	char	**temp;
	char	**tmp_tmp;

	t_point a_point;

	//a_point = NULL;
	//printf("-3\n");
	a_point.x = -1;
	a_point.y = -1;
	//printf("-2\n");
	temp = malloc(sizeof(char *) * (map->map_line_count + 1));
	if (!temp)
		return (1);
	//printf("-1\n");
	if (copy_map_line(map, temp))
		return (1);
	//printf("0\n");
	tmp_tmp = temp;
	ft_flood_fill(temp, (t_point){map->coloum_count, map->map_line_count},
		get_player_pos(map));
	//printf("1\n");
	//find every zero
	temp = tmp_tmp;
	while (find_zeros(&a_point, temp))
	{
		ft_flood_fill(temp, (t_point){map->coloum_count, map->map_line_count},
			a_point);
		temp = tmp_tmp;
	}
	//printf("2\n");
	//print_matrix(tmp_tmp);
	//printf("3\n");

	if (check_leak(temp, (t_point){map->coloum_count, map->map_line_count}))
		return (free_temp_map(temp, map->map_line_count, 1));
	return (free_temp_map(temp, map->map_line_count, 0));
}
