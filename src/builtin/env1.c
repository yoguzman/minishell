/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:24:20 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/27 16:24:21 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_list		*strdup_lst(t_list *my_env)
{
	t_list	*tmp;
	void	*buff;

	tmp = NULL;
	while (my_env)
	{
		if ((buff = ft_strdup((char *)my_env->content)) == NULL)
			return (NULL);
		if (list_push_back(&tmp, buff, 0) == -1)
			return (NULL);
		my_env = my_env->next;
	}
	return (tmp);
}

void		disp_env(t_list *tmp)
{
	while (tmp)
	{
		ft_putendl(tmp->content);
		tmp = tmp->next;
	}
}

int			equal(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		++i;
	}
	return (0);
}
