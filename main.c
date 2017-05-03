/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stoupin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 17:10:55 by stoupin           #+#    #+#             */
/*   Updated: 2017/04/28 17:34:43 by stoupin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "fillit.h"

void	ft_putstr(char *s)
{
	int len;
	
	len = 0;
	while(s[len] != '\0')
		len++;
	write(1, s, len);
}

int	print_usage(char *argv0)
{
	ft_putstr("Usage: ");
	ft_putstr(argv0);
	ft_putstr(" filename\n");
	return (1);
}

int	print_error(void)
{
	ft_putstr("error\n");
	return (1);
}

static void	print_board(t_env *env)
{
	char	board[env->a * env->a];
	int		i_tetri;
	int 	i_block;
	int		i;
	int		j;
	t_tetrimino	*t;
	
	i = 0;
	while (i < env->a * env->a)
		board[i++] = '.';
	i_tetri = -1;
	while (++i_tetri < env->n_tetriminos)
	{
		i_block = -1;
		while (++i_block < 4)
		{
			t = env->tetri_list + i_tetri;
			i = t->pos / 11 + t->c[i_block].i;
			j = t->pos % 11 + t->c[i_block].j;
			board[i * env->a + j] = 'A' + i_tetri;
		}
	}
	i = -1;
	while (++i < env->a)
	{
		write(1, board + (env->a * i), env->a);
		write(1, "\n", 1);
	}
}

int main(int argc, char **argv)
{
	int			fd;
	int			err;
	t_env		env;
	
	if (argc != 2)
		return (print_usage(argv[0]));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (print_error());
	err = read_tetriminos(fd, &env);
	if (err)
		return (print_error());
	close(fd);
	err = preprocess_tetriminos(&env);
	if (err)
		return (print_error());
	solve(&env);
	print_board(&env);
	return (1);
}