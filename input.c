/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:10:55 by stoupin           #+#    #+#             */
/*   Updated: 2017/04/28 17:34:43 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fillit.h"

static int	read_or_die(int fd, char *allowed_chars, char *c)
{
	int	ret;
	int	i;

	ret = read(fd, c, 1);
	if (ret == 0)
		return (1);
	i = 0;
	while (allowed_chars[i] != '\0')
	{
		if (*c == allowed_chars[i])
			return (0);
		i++;
	}
	return (1);
}

static int	parse_tetrimino(char array[4][4], t_tetrimino *tetri)
{
	int i;
	int j;
	int n;

	n = 0;
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (array[i][j] == '#')
			{
				if (n == 4)
					return (1);
				tetri->c[n].i = i;
				tetri->c[n].j = j;
				n++;
			}
			j++;
		}
		i++;
	}
	return (n != 4);
}

static int	read_tetrimino(int fd, t_tetrimino *tetri)
{
	int		i;
	int		j;
	char	array[4][4];
	char	dummy;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (read_or_die(fd, ".#", &(array[i][j])))
				return (1);
			j++;
		}
		if (read_or_die(fd, "\n", &dummy))
			return (1);
		i++;
	}
	return (parse_tetrimino(array, tetri));
}

int			read_tetriminos(int fd, t_env *env)
{
	int		i;
	int		err;
	int		ret;
	char	line_jump;

	env->n_tetriminos = 0;
	i = 0;
	while (i < 26)
	{
		err = read_tetrimino(fd, env->tetri_list + i);
		if (err)
			return (1);
		i++;
		ret = read(fd, &line_jump, 1);
		if (ret == 0)
			break ;
		if (line_jump != '\n')
			return (1);
	}
	env->n_tetriminos = i;
	return (0);
}
