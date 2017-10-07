/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:24:54 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/03 18:02:11 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "msh.h"

int			unsetenv_go(t_list **my_env, char *str)
{
	t_list	*tmp;

	tmp = *my_env;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, str,
						pos_eg((char *)tmp->content)) == 0)
		{
			free(tmp->content);
			ft_lstdel_double(my_env, tmp);
			free(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			ft_unsetenv(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7])
{
	(void)dl;
	(void)ab;
	if (!(tab[0] && tab[1]))
	{
		ft_puterr("unsetenv: too many arguments\n");
		return (3);
	}
	if (unsetenv_go(my_env, tab[1]) == 1)
		return (1);
	ft_puterr("unsetenv: no such variable: ");
	ft_puterr(tab[1]);
	ft_puterr("\n");
	return (3);
}
