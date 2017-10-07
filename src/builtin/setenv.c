/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:24:39 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/27 16:24:40 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			pos_eg(char *lol)
{
	int		nb;

	nb = 0;
	while (lol[nb])
	{
		if (lol[nb] == '=')
			return (nb);
		++nb;
	}
	return (-1);
}

t_list		*var_here_or_not(t_list *my_env, char *var)
{
	while (my_env)
	{
		if (ft_strncmp((char *)my_env->content, var,
						pos_eg((char *)my_env->content)) == 0)
			return (my_env);
		my_env = my_env->next;
	}
	return (NULL);
}

int			setenv_push(t_list **my_env, char *var, char *word)
{
	char	*new;
	char	*buff;
	t_list	*tmp;

	buff = ft_strjoin(var, "=");
	if ((new = ft_strjoin(buff, word)) == NULL)
		return (ft_puterr("fail strjoin\n"));
	free(buff);
	if ((tmp = var_here_or_not(*my_env, var)) != NULL)
	{
		free(tmp->content);
		tmp->content = new;
	}
	else
	{
		if (list_push_back(my_env, new, sizeof(new)) == -1)
			return (ft_puterr("list_push_back fail in func add_elem_to_env\n"));
	}
	return (0);
}

int			ft_setenv(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7])
{
	(void)dl;
	(void)ab;
	if (tab[1] && tab[2])
	{
		if (setenv_push(my_env, tab[1], tab[2]) == -1)
			return (3);
	}
	else
	{
		ft_puterr("setenv: too many arguments\n");
		return (3);
	}
	return (1);
}
