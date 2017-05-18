/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 18:37:42 by stoupin           #+#    #+#             */
/*   Updated: 2017/05/03 11:14:28 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static inline int	find_next_spot(t_coord *dim, __uint128_t *board,
									__uint128_t *tetri, int *pos)
{
	__uint128_t	overlap;

	(*pos)++;
	while (*pos / 11 <= dim->i)
	{
		while (*pos % 11 <= dim->j)
		{
			overlap = *board & (*tetri << *pos);
			if (overlap == 0)
				return (1);
			(*pos)++;
		}
		*pos += 11 - 1 - dim->j;
	}
	return (0);
}

static inline void	place_or_remove_tetrimino(__uint128_t *board,
												__uint128_t *tetri, int pos)
{
	*board ^= (*tetri << pos);
}

static int			solve_recursive(t_env *env, __uint128_t *board, int placed)
{
	int			pos;
	__uint128_t	tetri_bin;
	t_coord		dim;
	t_tetrimino	*tetri_list;

	if (placed == env->n_tetriminos)
		return (1);
	tetri_list = env->tetri_list;
	tetri_bin = tetri_list[placed].bin;
	pos = -1;
	if (tetri_list[placed].identical >= 0)
	{
		pos = tetri_list[tetri_list[placed].identical].pos;
	}
	dim = coordinates(env->a - tetri_list[placed].dim.i,
						env->a - tetri_list[placed].dim.j);
	while (find_next_spot(&dim, board, &tetri_bin, &pos))
	{
		place_or_remove_tetrimino(board, &tetri_bin, pos);
		tetri_list[placed].pos = pos;
		if (solve_recursive(env, board, placed + 1))
			return (1);
		place_or_remove_tetrimino(board, &tetri_bin, pos);
	}
	return (0);
}

int					solve(t_env *env)
{
	__uint128_t	board;
	int			solution_found;

	solution_found = 0;
	env->a = 2;
	while (env->a * env->a < env->n_tetriminos * 4)
		(env->a)++;
	while (1)
	{
		board = 0;
		solution_found = solve_recursive(env, &board, 0);
		if (solution_found)
			break ;
		(env->a)++;
	}
	return (0);
}
