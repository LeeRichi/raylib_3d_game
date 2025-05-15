/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:21:19 by chlee2            #+#    #+#             */
/*   Updated: 2025/05/15 15:05:59 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	flood_fill(char **tab, t_point size, t_point begin)
{
	char	c;
	t_point	new;

	c = tab[begin.y][begin.x];
	tab[begin.y][begin.x] = 'F';
	if (begin.x > 0 && tab[begin.y][begin.x - 1] == c)
	{
		new = begin;
		new.x--;
		flood_fill(tab, size, new);
	}
	if (begin.x < (size.x - 1) && tab[begin.y][begin.x + 1] == c)
	{
		new = begin;
		new.x++;
		flood_fill(tab, size, new);
	}
	if (begin.y > 0 && tab[begin.y - 1][begin.x] == c)
	{
		new = begin;
		new.y--;
		flood_fill(tab, size, new);
	}
	if (begin.y < (size.y - 1) && tab[begin.y + 1][begin.x] == c)
	{
		new = begin;
		new.y++;
		flood_fill(tab, size, new);
	}
}
