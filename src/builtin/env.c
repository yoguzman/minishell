/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:24:13 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/28 15:34:40 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int			env_u(t_list **tmp, char **tab, int *i)
{
	if (tab[*i + 1])
	{
		if (equal(tab[*i + 1]) || tab[*i + 1] == NULL || tab[*i + 1][0] == '\0')
		{
			ft_puterr("env: unsetenv : Invalid argument\n");
			return (2);
		}
		unsetenv_go(tmp, tab[*i + 1]);
		++*i;
	}
	else
	{
		ft_puterr("usage: env [-i] [-u name] ");
		ft_puterr("[name=value ...] [commande [args...]]\n");
		return (2);
	}
	return (0);
}

static int	check_arg(t_list **tmp, char **tab, int *i)
{
	while (tab[*i])
	{
		if (!(tab[*i][0] == '-'))
			return (0);
		if (ft_strcmp(tab[*i], "-u") == 0)
		{
			if (env_u(tmp, tab, i) == 2)
				return (2);
		}
		else if (ft_strcmp(tab[*i], "-i") == 0)
		{
			free_list(*tmp);
			*tmp = NULL;
		}
		else
		{
			return (3);
		}
		++*i;
	}
	return (0);
}

int			put_equal(t_list **tmp, char **tab, int *i)
{
	while (tab[*i])
	{
		if (equal(tab[*i]) == 1)
		{
			if (list_push_back(tmp, tab[*i], sizeof(tmp)) == -1)
				return (-1);
		}
		else
			return (0);
		++*i;
	}
	return (0);
}

char		*reforme_cmd(char **tab, int i)
{
	char	*cmd;
	char	*buff;

	if ((cmd = ft_strdup(tab[i])) == NULL)
		return (NULL);
	while (tab[i + 1])
	{
		buff = cmd;
		if ((cmd = ft_strjoin(cmd, " ")) == NULL)
			return (NULL);
		free(buff);
		buff = cmd;
		if ((cmd = ft_strjoin(cmd, tab[i + 1])) == NULL)
			return (NULL);
		free(buff);
		++i;
	}
	return (cmd);
}

int			ft_env(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7])
{
	t_list	*tmp;
	int		i;
	char	*cmd;

	i = 1;
	tmp = strdup_lst(*my_env);
	if (check_arg(&tmp, tab, &i) == 2)
		return (3);
	if (put_equal(&tmp, tab, &i) == -1)
		return (3);
	if (tab[i] == NULL)
		disp_env(tmp);
	else
	{
		if ((cmd = reforme_cmd(tab, i)) == NULL)
			return (3);
		if (exec(cmd, &tmp, dl, ab) == -1)
			return (-1);
		free(cmd);
	}
	free_list(tmp);
	return (1);
}
