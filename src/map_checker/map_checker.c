/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:38:08 by chlee2            #+#    #+#             */
/*   Updated: 2025/05/14 12:04:35 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int has_invalid_char(t_map *map)
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
				map->player_pos_x = j;
				map->player_pos_y = i;
				if(found_player_flag)
				{
					printf("Error\nFound more than 1 player\n");
					return (1);
				}
				found_player_flag = 1;
			}
			if (map->map[i][j] != '1' && map->map[i][j] != '0' && map->map[i][j] != 'N'
				&& map->map[i][j] != 'S' && map->map[i][j] != 'E' && map->map[i][j] != 'W' && map->map[i][j] != '\0') //gpt says '\0' chekc is redundant but it doesnt work without it
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

//utils
void skip_spaces(char **map, int *i, int *j)
{
	while (map[*i][*j] == ' ' || map[*i][*j] == '\t'
		|| map[*i][*j] == '\r'
		|| map[*i][*j] == '\v' || map[*i][*j] == '\f')
		(*j)++;
}

int	is_surroundings_valid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while(map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			skip_spaces(map->map, &i, &j);
			if (i == 0 || i == map->map_line_count - 1
				|| j == 0 || (size_t)j == ft_strlen(map->map[i]) - 1)
			{
				if (map->map[i][j] != '1' && map->map[i][j] != '\0')
				{
					printf("Error\nMap is not surrounded by walls.\n");
					return (0);
				}

			}
			j++;
		}
		i++;
	}
	return (1);
}

int	player_can_see_wall(t_map *map) //later can split this to module functions
{
	int i;
	int j;

	i = map->player_pos_y;
	j = map->player_pos_x;
	//see up
	while (i > 0 && map->map[i - 1][j] == '0')
		i--;
	if (i - 1 < 0 || map->map[i - 1][j] != '1')
		return (0);
	//see down
	i = map->player_pos_y;
	j = map->player_pos_x;
	while (map->map[i + 1] && map->map[i + 1][j] == '0')
		i++;
	if (map->map[i + 1][j] != '1')
		return (0);
	//see left
	i = map->player_pos_y;
	j = map->player_pos_x;
	while (j > 0 && map->map[i][j - 1] == '0')
		j--;
	if (map->map[i][j - 1] != '1')
		return (0);
	//see right
	i = map->player_pos_y;
	j = map->player_pos_x;
	while (map->map[i][j + 1] && map->map[i][j + 1] == '0')
		j++;
	if (map->map[i][j + 1] != '1')
		return (0);
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

//temp
void print_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
}

int	map_checker(t_map *map) //returm 1 if fail
{
	print_map(map);

	//check colors
	if (!is_valid_color(map->floor_color))
	{
		printf("Error\nInvalid floor color.\n");
		exit(EXIT_FAILURE);
	}
	if (map->floor_color == map->ceiling_color)
	{
		printf("Error\nFloor and ceiling colors cannot be the same.\n");
		exit(EXIT_FAILURE);
	}

	//check invalid characters
	if (has_invalid_char(map))
	{
		printf("Error\nInvalid character in map.\n");
		exit(EXIT_FAILURE);
	}

	//dubug
	printf("player pos x: %d, y: %d\n", map->player_pos_x, map->player_pos_y);

	//check border
	if (!is_surroundings_valid(map))
	{
		printf("Error\nMap is not surrounded by walls.\n");
		exit(EXIT_FAILURE);
	}

	if (!player_can_see_wall(map))
	{
		printf("Error\nPlayer cannot see wall.\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
