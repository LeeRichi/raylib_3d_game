/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:21:19 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/05 12:03:16 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	flood_fill_helper(t_point *new, t_point begin, char c, int is_plus)
{
	*new = begin;
	if (c == 'x')
	{
		if (is_plus)
			new->x++;
		else
			new->x--;
	}
	else if (c == 'y')
	{
		if (is_plus)
			new->y++;
		else
			new->y--;
	}
}

//temp
void print_size(t_point size)
{
	printf("Size: %d x %d\n", size.x, size.y);
}

void	flood_fill(char **tab, t_point size, t_point begin)
{
	char	c;
	t_point	new;

	// temp
	print_size(size);

	c = tab[begin.y][begin.x];
	tab[begin.y][begin.x] = 'F';
	if (begin.x > 0 && tab[begin.y][begin.x - 1] == c)
	{
		flood_fill_helper(&new, begin, 'x', 0);
		flood_fill(tab, size, new);
	}
	if (begin.x < (size.x - 1) && tab[begin.y][begin.x + 1] == c)
	{
		flood_fill_helper(&new, begin, 'x', 1);
		flood_fill(tab, size, new);
	}
	if (begin.y > 0 && tab[begin.y - 1][begin.x] == c)
	{
		flood_fill_helper(&new, begin, 'y', 0);
		flood_fill(tab, size, new);
	}
	if (begin.y < (size.y - 1) && tab[begin.y + 1][begin.x] == c)
	{
		flood_fill_helper(&new, begin, 'y', 1);
		flood_fill(tab, size, new);
	}
}
