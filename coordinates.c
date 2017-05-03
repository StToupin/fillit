/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetrimino.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 12:39:57 by stoupin           #+#    #+#             */
/*   Updated: 2017/04/13 19:25:48 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_coord		coordinates(int i, int j)
{
	t_coord	c;

	c.i = i;
	c.j = j;
	return (c);
}

void		coord_minmax(t_coord *c_min, t_coord *c_max, t_coord c_new)
{
	if (c_new.i < c_min->i)
		c_min->i = c_new.i;
	if (c_new.j < c_min->j)
		c_min->j = c_new.j;
	if (c_new.i > c_max->i)
		c_max->i = c_new.i;
	if (c_new.j > c_max->j)
		c_max->j = c_new.j;
}

int			is_next_to(t_coord *a, t_coord *b)
{
	if (a->i == b->i && a->j + 1 == b->j)
		return (1);
	if (a->i == b->i && a->j - 1 == b->j)
		return (1);
	if (a->j == b->j && a->i + 1 == b->i)
		return (1);
	if (a->j == b->j && a->i - 1 == b->i)
		return (1);
	return (0);
}

int			equal_coords(t_coord c1, t_coord c2)
{
	return (c1.i == c2.i && c1.j == c2.j);
}
