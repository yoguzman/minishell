/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:24:04 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/27 16:46:35 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int				condition_put_all(char *str, int *i, int *n)
{
	if (str[*i] == 'a')
		ft_putchar('\a');
	else if (str[*i] == 'b')
		ft_putchar('\b');
	else if (str[*i] == 'c' && (*n = 1) == 1)
		return (1);
	else if (str[*i] == 'f')
		ft_putchar('\f');
	else if (str[*i] == 'n')
		ft_putchar('\n');
	else if (str[*i] == 'r')
		ft_putchar('\r');
	else if (str[*i] == 't')
		ft_putchar('\t');
	else if (str[*i] == 'v')
		ft_putchar('\v');
	else if (str[*i] == '\\')
		ft_putchar('\\');
	else if (str[*i] == '0')
		go_octal(str, i);
	else
		--*i;
	return (0);
}

int				put_all(char *str, int *n)
{
	int			i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			++i;
			if (condition_put_all(str, &i, n) == 1)
				return (1);
		}
		else
			ft_putchar(str[i]);
		++i;
	}
	return (0);
}

static void		affiche(char **tab, int i, int e, int *n)
{
	if (e == 0)
		while (tab[i])
		{
			ft_putstr(tab[i]);
			if (tab[i + 1])
				ft_putchar(' ');
			++i;
		}
	else
		while (tab[i])
		{
			if (put_all(tab[i], n) == 1)
				return ;
			if (tab[i + 1])
				ft_putchar(' ');
			++i;
		}
}

static void		check_arg(char **tab, int *i, int *e, int *n)
{
	int			j;
	int			el;
	int			nl;

	while (tab[*i])
	{
		if (tab[*i][0] != '-')
			return ;
		j = 1;
		el = 0;
		nl = 0;
		while (tab[*i][j])
		{
			if (tab[*i][j] != 'e' && tab[*i][j] != 'n' &&
					!(*e = 0) &&
					!(*n = 0))
				return ;
			el = (tab[*i][j] == 'e' ? 1 : 0);
			nl = (tab[*i][j] == 'n' ? 1 : 0);
			*e = (*e == 0) ? el : *e;
			*n = (*n == 0) ? nl : *n;
			++j;
		}
		++*i;
	}
}

int				ft_echo(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7])
{
	int			i;
	int			e;
	int			n;

	(void)dl;
	(void)ab;
	i = 1;
	e = 0;
	n = 0;
	(void)my_env;
	check_arg(tab, &i, &e, &n);
	affiche(tab, i, e, &n);
	if (n == 0)
		ft_putchar('\n');
	return (1);
}
