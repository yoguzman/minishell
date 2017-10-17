/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_fill_cmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:37:21 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/09 13:21:20 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "msh.h"

int				check_path_for_exec(char *path, char **tab, int ret)
{
	if (path == NULL)
	{
		ft_puterr("msh: command not found: ");
		ft_puterr(tab[0]);
		ft_puterr("\n");
		return (1);
	}
	else if (ret == -2)
	{
		ft_puterr("msh: permission denied: ");
		ft_puterr(tab[0]);
		ft_puterr("\n");
		return (1);
	}
	return (0);
}

int				exec(char *cmd, t_list **my_env, t_dl *dl, t_ab ab[7])
{
	char		**tab;
	char		*path;
	int			ret;

	if ((tab = ft_strsplit(cmd, "\f\r\t \n\v")) == NULL)
		return (ft_puterr("strsplit fail in read and fill cmd\n"));
	if ((ret = check_bultins(tab, ab, my_env, dl)) == -1 || ret == 1 ||
													ret == 2 || ret == 3)
	{
		dl->ret_cmd = (ret == 3 ? 31 : 32);
		return (ret);
	}
	if ((path = ft_strdup(tab[0])) == NULL)
		return (ft_puterr("strdup fail in read and fill cmd\n"));
	if ((ret = find_path(&path, *my_env, dl)) == -1)
		return (-1);
	if (check_path_for_exec(path, tab, ret) == 0)
		if (exec_cmd_if_ok(path, tab, *my_env, dl) == -1)
			return (-1);
	free(path);
	free_tab(tab);
	return (0);
}

int				exec_cmd(t_ab ab[7], t_dl *dl, t_list **my_env)
{
	char		**tab;
	int			i;
	int			ret;

	if (check_blank_line(dl->line))
		return (0);
	if ((tab = ft_strsplit(dl->line, ";")) == NULL)
		return (ft_puterr("strsplit fail in read and fill cmd\n"));
	i = 0;
	while (tab[i])
	{
		if (tokenzer(&(tab[i]), *my_env) == -1)
			return (-1);
		if ((ret = exec(tab[i], my_env, dl, ab)) == -1 || ret == 2)
			return (ret);
		++i;
	}
	free_tab(tab);
	return (0);
}
