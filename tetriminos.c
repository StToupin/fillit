/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetriminos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:32:56 by stoupin           #+#    #+#             */
/*   Updated: 2017/05/03 11:14:38 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	move_to_topleft_calculate_dim(t_tetrimino *t)
{
	int		n;
	t_coord	c_topleft;
	t_coord	c_bottomright;

	c_topleft = coordinates(4, 4);
	c_bottomright = coordinates(-1, -1);
	coord_minmax(&c_topleft, &c_bottomright, t->c[0]);
	coord_minmax(&c_topleft, &c_bottomright, t->c[1]);
	coord_minmax(&c_topleft, &c_bottomright, t->c[2]);
	coord_minmax(&c_topleft, &c_bottomright, t->c[3]);
	t->dim.i = c_bottomright.i - c_topleft.i + 1;
	t->dim.j = c_bottomright.j - c_topleft.j + 1;
	n = 0;
	while (n < 4)
	{
		t->c[n].i -= c_topleft.i;
		t->c[n].j -= c_topleft.j;
		n++;
	}
}

static int	check_tetrimino(t_tetrimino *t)
{
	int		a;
	int		b;
	int		n_junctions;

	a = 0;
	n_junctions = 0;
	while (a < 4)
	{
		b = 0;
		while (b < 4)
		{
			if (is_next_to(&(t->c[a]), &(t->c[b])))
				n_junctions++;
			b++;
		}
		a++;
	}
	if (n_junctions == 6 || n_junctions == 8)
		return (1);
	else
		return (0);
}

static void	calculate_binary_representation(t_tetrimino *t)
{
	int			n;
	__uint128_t	one;
	int			pos;

	t->bin = 0;
	one = 1;
	n = 0;
	while (n < 4)
	{
		pos = t->c[n].i * 11 + t->c[n].j;
		t->bin |= one << pos;
		n++;
	}
}

int			preprocess_tetriminos(t_env *env)
{
	int			a;
	int			b;
	t_tetrimino	*t;

	a = 0;
	while (a < env->n_tetriminos)
	{
		t = env->tetri_list + a;
		move_to_topleft_calculate_dim(t);
		calculate_binary_representation(t);
		if (!check_tetrimino(t))
			return (1);
		t->identical = -1;
		b = 0;
		while (b < a)
		{
			if (env->tetri_list[a].bin == env->tetri_list[b].bin)
				t->identical = b;
			b++;
		}
		a++;
	}
	return (0);
}
