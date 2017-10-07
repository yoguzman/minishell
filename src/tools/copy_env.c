/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:37:52 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/27 16:40:08 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "msh.h"

int			add_elem_to_env(t_list **my_env, char *add_env, int add_beg_or_last)
{
	char	*cpy_env;
	t_list	*new;

	if ((cpy_env = ft_strdup(add_env)) == NULL)
		return (ft_puterr("ft_strdup fail in func add_elem_to_env\n"));
	if (add_beg_or_last == LAST)
	{
		if (list_push_back(my_env, cpy_env, sizeof(add_env)) == -1)
			return (ft_puterr("list_push_back fail in func add_elem_to_env\n"));
		return (0);
	}
	if ((new = malloc(sizeof(t_list))) == NULL)
		return (ft_puterr("malloc fail in func add_elem_to_env\n"));
	new->content = cpy_env;
	ft_lstadd_double(my_env, new);
	return (0);
}

t_list		*copy_env(char **env)
{
	t_list	*my_env;

	my_env = NULL;
	if (env && *env)
		while (*env)
		{
			if (add_elem_to_env(&my_env, *env, BEGIN) == -1)
				return (ft_puterr_null("add_elem fail in func copy env\n"));
			++env;
		}
	return (my_env);
}
