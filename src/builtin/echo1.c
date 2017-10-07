/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:23:41 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/27 16:23:43 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_isdigit_oct(char c)
{
	if ((c >= '0' && c <= '7'))
		return (1);
	return (0);
}

void			disp_oct(char *buff, int octal, int *ai, int nb)
{
	octal = ft_atoi_oct(buff);
	ft_putchar((char)octal);
	*ai += nb;
}

void			fill_buff(char *buff, char *str, int i, int nb)
{
	int			n;

	n = 0;
	while (nb > 0)
	{
		buff[n] = str[i + n + 1];
		++n;
		--nb;
	}
}

int				condition_oct(char *str, int *ai)
{
	int			octal;
	char		buff[4];
	int			i;

	i = *ai;
	octal = 0;
	ft_memset(buff, 0, 4);
	if (str[i + 1])
		if (ft_isdigit_oct(str[i + 1]))
		{
			fill_buff(buff, str, i, 1);
			disp_oct(buff, octal, ai, 1);
			return (1);
		}
	return (0);
}

int				go_octal(char *str, int *ai)
{
	int			octal;
	char		buff[4];
	int			i;

	i = *ai;
	octal = 0;
	ft_memset(buff, 0, 4);
	if (str[i + 1] && str[i + 2] && str[i + 3])
		if (ft_isdigit_oct(str[i + 1]) && ft_isdigit_oct(str[i + 2]) &&
			ft_isdigit_oct(str[i + 3]))
		{
			fill_buff(buff, str, i, 3);
			disp_oct(buff, octal, ai, 3);
			return (0);
		}
	if (str[i + 1] && str[i + 2])
		if (ft_isdigit_oct(str[i + 1]) && ft_isdigit_oct(str[i + 2]))
		{
			fill_buff(buff, str, i, 2);
			disp_oct(buff, octal, ai, 2);
			return (0);
		}
	if (condition_oct(str, ai) == 1)
		return (0);
	return (1);
}
