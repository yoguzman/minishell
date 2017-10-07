/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:38:28 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/27 16:38:29 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char			*disp_pwd(char *ret)
{
	int			i;
	int			slash;

	i = 0;
	slash = 0;
	while (ret[i])
		++i;
	--i;
	while (i >= 0 && slash != 2)
	{
		if (ret[i] == '/')
			++slash;
		--i;
	}
	if (i == -1)
		return (ret + i + 1);
	return (ret + i + 2);
}

void			set_color(int i[6])
{
	int			j;

	j = 0;
	while (j <= 5)
	{
		if (j == 0)
			i[0] = i[0] + 1;
		else
			i[j] = i[j - 1] + 1;
		if (i[j] > 36 || i[j] < 31)
			i[j] = 31;
		++j;
	}
}

void			prompt_turfu(t_list *my_env)
{
	char		*ret;
	static int	i[6];

	set_color(i);
	ft_putstr_color("[", i[0]);
	if ((ret = ft_getenv("USER=", my_env)))
		ft_putstr_color(ret, i[1]);
	else
		ft_putstr_color("?", i[1]);
	ft_putstr_color("-", i[2]);
	ft_putstr_color(">", i[3]);
	if ((ret = ft_getenv("PWD=", my_env)))
		ft_putstr_color(disp_pwd(ret), i[4]);
	else
		ft_putstr_color("?", i[4]);
	ft_putstr_color("]", i[5]);
}
