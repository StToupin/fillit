/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:29:10 by stoupin           #+#    #+#             */
/*   Updated: 2017/05/03 11:14:44 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

typedef struct	s_coord
{
	int	i;
	int	j;
}				t_coord;

typedef struct	s_tetrimino
{
	t_coord		dim;
	t_coord		c[4];
	__uint128_t	bin;
	int			pos;
	int			identical;
}				t_tetrimino;

typedef struct	s_env
{
	int			a;
	int			n_tetriminos;
	t_tetrimino	tetri_list[26];
}				t_env;

/*
** From input.c
*/

int				read_tetriminos(int fd, t_env *env);

/*
** From coordinates.c
*/

t_coord			coordinates(int i, int j);
void			coord_minmax(t_coord *c_min, t_coord *c_max, t_coord c_new);
int				is_next_to(t_coord *a, t_coord *b);
int				equal_coords(t_coord c1, t_coord c2);

/*
** From tetriminos.c
*/

int				preprocess_tetriminos(t_env *env);

/*
** From solve.c
*/

int				solve(t_env *env);

#endif
