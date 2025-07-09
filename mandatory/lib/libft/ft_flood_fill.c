/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flood_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chlee2 <chlee2@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:51:18 by chlee2            #+#    #+#             */
/*   Updated: 2025/07/05 13:13:18 by chlee2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	try_fill(char **t, t_point sz, int x, int y)
{
	t_point	next;

	next.x = x;
	next.y = y;
	if (x < 0 || y < 0 || x >= sz.x || y >= sz.y)
		return ;
	if (t[y][x] == '1' || t[y][x] == 'F')
		return ;
	ft_flood_fill(t, sz, next);
}

void	ft_flood_fill(char **t, t_point sz, t_point b)
{
	t[b.y][b.x] = 'F';
	try_fill(t, sz, b.x - 1, b.y);
	try_fill(t, sz, b.x + 1, b.y);
	try_fill(t, sz, b.x, b.y - 1);
	try_fill(t, sz, b.x, b.y + 1);
}
