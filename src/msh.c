/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:38:25 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/28 14:34:05 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "msh.h"

int				fill_line(t_dl *dl, t_ak ak[9])
{
	int			ret1;
	int			ret;

	ft_memset(dl->buff, 0, 4);
	dl->line = NULL;
	dl->comple_hist = NULL;
	dl->pos_curs = 0;
	while ((ret = read(0, dl->buff, 3)) > 0)
	{
		if (!(dl->line))
			dl->pos_curs = 0;
		if (((ret1 = edit_line(dl, ak)) == 1 || ret1 == -1 || ret1 == 3))
			return (ret1);
		if (ret1 != 2)
			ft_memset(dl->buff, 0, 4);
		else
		{
			ft_putchar('\n');
			return (0);
		}
	}
	return (0);
}

int				line_fill(t_dl *dl, t_ak ak[9], t_ab ab[7])
{
	int			ret;

	if ((ret = fill_line(dl, ak)) != 0)
	{
		if (ret == 3)
			return (0);
		free_list(dl->cmd_hist);
		free_ab(ab);
		return (ret);
	}
	return (0);
}

int				while_msh(t_list **my_env)
{
	t_dl		dl;
	t_ak		ak[9];
	t_ab		ab[7];
	int			ret;

	dl.cmd_hist = NULL;
	init_ak(ak);
	if (init_ab(ab) == -1)
		return (-1);
	dl.ret_cmd = 32;
	while (42)
	{
		prompt_turfu(*my_env);
		ft_putstr_color(" % ", dl.ret_cmd);
		if ((ret = line_fill(&dl, ak, ab)) != 0)
			return (ret);
		if ((dl.cmd_hist == NULL && dl.line != NULL) ||
				(dl.line && (ft_strcmp(dl.cmd_hist->content, dl.line))))
			ft_lstadd_double(&(dl.cmd_hist),
					ft_lstnew(dl.line, ft_strlen(dl.line) + 1));
		if ((ret = exec_cmd(ab, &dl, my_env)) == -1 || ret == 2)
			return (ret);
		free(dl.line);
	}
	return (0);
}
