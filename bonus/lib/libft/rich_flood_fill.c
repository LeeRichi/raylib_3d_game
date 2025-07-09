/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rich_flood_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:51:18 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/05 13:13:18 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//t = tab, sz = size, b = begin
// void	rich_flood_fill(char **t, t_point sz, t_point b)
// {
// 	t[b.y][b.x] = 'F';
// 	if (b.x > 0 && t[b.y][b.x - 1] != '1' && t[b.y][b.x - 1] != 'F')
// 	{
// 		b.x = b.x - 1;
// 		rich_flood_fill(t, sz, b);
// 	}
// 	if (b.x < (sz.x - 1) && t[b.y][b.x + 1] != '1' && t[b.y][b.x + 1] != 'F')
// 	{
// 		b.x = b.x + 1;
// 		rich_flood_fill(t, sz, b);
// 	}
// 	if (b.y > 0 && t[b.y - 1][b.x] != '1' && t[b.y - 1][b.x] != 'F')
// 	{
// 		b.y = b.y - 1;
// 		rich_flood_fill(t, sz, b);
// 	}
// 	if (b.y < (sz.y - 1) && t[b.y + 1][b.x] != '1' && t[b.y + 1][b.x] != 'F')
// 	{
// 		b.y = b.y + 1;
// 		rich_flood_fill(t, sz, b);
// 	}
// }

// void	rich_flood_fill(char **t, t_point sz, t_point b)
// {
// 	t[b.y][b.x] = 'F';
// 	t_point new_point;

// 	if (b.x > 0 && t[b.y][b.x - 1] != '1' && t[b.y][b.x - 1] != 'F')
// 	{
// 		t_point left = {b.x - 1, b.y};
// 		rich_flood_fill(t, sz, left);
// 	}
// 	if (b.x < (sz.x - 1) && t[b.y][b.x + 1] != '1' && t[b.y][b.x + 1] != 'F')
// 	{
// 		t_point right = {b.x + 1, b.y};
// 		rich_flood_fill(t, sz, right);
// 	}
// 	if (b.y > 0 && t[b.y - 1][b.x] != '1' && t[b.y - 1][b.x] != 'F')
// 	{
// 		t_point up = {b.x, b.y - 1};
// 		rich_flood_fill(t, sz, up);
// 	}
// 	if (b.y < (sz.y - 1) && t[b.y + 1][b.x] != '1' && t[b.y + 1][b.x] != 'F')
// 	{
// 		t_point down = {b.x, b.y + 1};
// 		rich_flood_fill(t, sz, down);
// 	}
// }

void	try_fill(char **t, t_point sz, int x, int y)
{
	if (x < 0 || y < 0 || x >= sz.x || y >= sz.y)
		return;
	if (t[y][x] == '1' || t[y][x] == 'F')
		return;

	t_point next = {x, y};
	rich_flood_fill(t, sz, next);
}

void	rich_flood_fill(char **t, t_point sz, t_point b)
{
	t[b.y][b.x] = 'F';

	try_fill(t, sz, b.x - 1, b.y); // Left
	try_fill(t, sz, b.x + 1, b.y); // Right
	try_fill(t, sz, b.x, b.y - 1); // Up
	try_fill(t, sz, b.x, b.y + 1); // Down
}
