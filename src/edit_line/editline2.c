/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editline2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:37:16 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/27 16:45:27 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			move_arrow_right(t_dl *dl)
{
	if (dl->buff[0] == 27 && dl->buff[1] == 91 && dl->buff[2] == 67)
	{
		if (dl->pos_curs < (int)ft_strlen(dl->line))
		{
			ft_putstr(dl->buff);
			++dl->pos_curs;
		}
	}
	return (0);
}

int			move_arrow_left(t_dl *dl)
{
	if (dl->buff[0] == 27 && dl->buff[1] == 91 &&
		dl->buff[2] == 68 && dl->pos_curs >= 0)
	{
		if (dl->pos_curs > 0)
		{
			ft_putstr(dl->buff);
			--dl->pos_curs;
		}
	}
	return (0);
}

void		put_space(t_dl *dl, char *str)
{
	while (dl->pos_curs > 0)
	{
		move_l_or_r(68);
		--dl->pos_curs;
	}
	while (dl->pos_curs < (int)ft_strlen(dl->line))
	{
		ft_putchar(' ');
		++dl->pos_curs;
	}
	while (dl->pos_curs > 0)
	{
		move_l_or_r(68);
		--dl->pos_curs;
	}
	ft_putstr(str);
	dl->pos_curs = ft_strlen(str);
}

int			completion_up(t_dl *dl)
{
	t_list	*cmd_hist;

	cmd_hist = dl->comple_hist;
	if (!cmd_hist)
		return (0);
	cmd_hist = cmd_hist->next;
	while (cmd_hist)
	{
		if (!ft_memcmp(dl->cmd_hist->content, cmd_hist->content,
						ft_strlen(dl->cmd_hist->content)))
		{
			dl->comple_hist = cmd_hist;
			put_space(dl, dl->comple_hist->content);
			free(dl->line);
			dl->line = ft_strdup(dl->comple_hist->content);
			return (0);
		}
		cmd_hist = cmd_hist->next;
	}
	return (0);
}

int			completion_down(t_dl *dl)
{
	t_list	*cmd_hist;

	cmd_hist = dl->comple_hist;
	if (!cmd_hist)
		return (0);
	cmd_hist = cmd_hist->prev;
	while (cmd_hist)
	{
		if (!ft_memcmp(dl->cmd_hist->content, cmd_hist->content,
						ft_strlen(dl->cmd_hist->content)))
		{
			dl->comple_hist = cmd_hist;
			put_space(dl, dl->comple_hist->content);
			free(dl->line);
			if (dl->comple_hist->content == NULL)
				dl->line = NULL;
			else
				dl->line = ft_strdup(dl->comple_hist->content);
			return (0);
		}
		cmd_hist = cmd_hist->prev;
	}
	return (0);
}
