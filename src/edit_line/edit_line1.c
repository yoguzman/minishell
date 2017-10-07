/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:36:30 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/27 16:45:45 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	move_l_or_r(int c_est_ma_direction)
{
	ft_putchar(27);
	ft_putchar(91);
	ft_putchar(c_est_ma_direction);
}

void	ft_cpy_char_to_i(char *line, char c, int pos)
{
	int	j;

	j = ft_strlen(line);
	while (j > pos)
	{
		line[j] = line[j - 1];
		--j;
	}
	line[j] = c;
}

int		cpy_char(t_dl *dl)
{
	int	j;

	if ((dl->line = ft_reallocfake(dl->line,
									ft_strlen(dl->line), 1 + 1)) == NULL)
		return (-1);
	ft_cpy_char_to_i(dl->line, dl->buff[0], dl->pos_curs);
	ft_putstr(dl->line + dl->pos_curs);
	++(dl->pos_curs);
	j = ft_strlen(dl->line);
	while (j > dl->pos_curs && j--)
		move_l_or_r(68);
	return (0);
}

void	ft_del_char_to_i(char *line, int pos)
{
	int	j;

	j = ft_strlen(line);
	if (j == 0)
		return ;
	--pos;
	while (j > pos)
	{
		line[pos] = line[pos + 1];
		++pos;
	}
	if (line)
		line[pos] = 0;
}

int		del_char(t_dl *dl)
{
	int	ret;

	if (dl->pos_curs <= 0)
		return (0);
	ret = 0;
	ft_del_char_to_i(dl->line, dl->pos_curs);
	move_l_or_r(68);
	ft_putstr(dl->line + dl->pos_curs - 1);
	ft_putchar(' ');
	while (ret <= (int)ft_strlen(dl->line + dl->pos_curs - 1) && ++ret)
		move_l_or_r(68);
	if (dl->line[0] == 0)
	{
		free(dl->line);
		dl->line = NULL;
	}
	else if ((dl->line =
				ft_reallocfake(dl->line, ft_strlen(dl->line), 1)) == NULL)
		return (-1);
	--dl->pos_curs;
	return (0);
}
