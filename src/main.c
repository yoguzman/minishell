/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:38:20 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/28 14:30:09 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int				main(int ac, char **av, char **env)
{
	t_list		*my_env;

	(void)ac;
	(void)av;
	my_env = copy_env(env);
	signal(SIGINT, &catch_ctrlc);
	set_term();
	if (while_msh(&my_env) == -1)
		return (-1);
	free_list(my_env);
	unset_term();
	return (0);
}
