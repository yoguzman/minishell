/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:37:47 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/09 13:13:04 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "msh.h"

int			tokenzer(char **line, t_list *my_env)
{
	int		i;
	int		ret;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '~' && i > 0 &&
				(*line)[i - 1] == ' ' &&
				((*line)[i + 1] == '/' || (*line)[i + 1] == ' ' ||
				(*line)[i + 1] == 0))
		{
			if ((ret = replace_tild(line, &i, my_env)) == -1)
				return (-1);
			if (ret != 2)
				i = -1;
		}
		++i;
	}
	return (0);
}
