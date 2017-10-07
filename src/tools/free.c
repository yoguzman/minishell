/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:37:58 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/27 16:37:59 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "msh.h"

void			free_list(t_list *list)
{
	t_list		*tmp;

	while (list)
	{
		free(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

void			free_first_list(t_dl *dl)
{
	free(dl->cmd_hist->content);
	dl->cmd_hist = dl->cmd_hist->next;
	free(dl->cmd_hist->prev);
	dl->cmd_hist->prev = NULL;
}

void			free_tab(char **tab)
{
	free(tab[0]);
	free(tab);
}

void			free_char(char **str)
{
	free(*str);
	*str = NULL;
}

void			free_ab(t_ab ab[7])
{
	int			i;

	i = 0;
	while (ab[i].f)
	{
		free(ab[i].bultins);
		++i;
	}
}
