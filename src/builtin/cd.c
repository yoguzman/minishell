/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:23:57 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/09 13:19:45 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "msh.h"

int			change_dir(t_list **my_env, char *path, char *new_path)
{
	(void)my_env;
	if (chdir(path) == -1)
	{
		if (access(path, F_OK) == -1)
			ft_puterr("cd: no such file or directory: ");
		else if (access(path, R_OK) == -1)
			ft_puterr("cd: permission denied: ");
		else
			ft_puterr("cd: not a directory: ");
		ft_puterr(path);
		ft_puterr("\n");
		free(path);
		free(new_path);
		return (-1);
	}
	return (0);
}

int			two_arg(t_list **my_env, char **tab, char *oldpwd)
{
	char	*new_path;
	char	*new_path_end;

	new_path = NULL;
	new_path_end = NULL;
	if (tab[1][0] == '/')
	{
		if ((new_path_end = ft_strdup(tab[1])) == NULL)
			return (ft_puterr("ft_strdup fail\n"));
	}
	else if (ft_strcmp(tab[1], "-") != 0 && tab[1][0] != '/')
	{
		new_path_end = ft_strjoin(oldpwd, "/");
		new_path = new_path_end;
		if ((new_path_end = ft_strjoin(new_path, tab[1])) == NULL)
			return (ft_puterr("ft_strjoin fail\n"));
	}
	else if (ft_strcmp(tab[1], "-") == 0 && ft_getenv("OLDPWD=", *my_env))
		if ((new_path_end = ft_strdup(ft_getenv("OLDPWD=", *my_env))) == NULL)
			return (-1);
	if (change_dir(my_env, new_path_end, new_path) == -1)
		return (-1);
	free(new_path);
	free(new_path_end);
	return (0);
}

int			one_arg(t_list **my_env)
{
	char	*home;

	if ((home = ft_getenv("HOME=", *my_env)) == NULL)
		return (0);
	if (change_dir(my_env, home, NULL) == -1)
		return (-1);
	if ((setenv_push(my_env, "PWD", home)) == -1)
		return (-1);
	return (0);
}

int			check_arg(t_list **my_env, char **tab, char *oldpwd)
{
	if (tab[1] == NULL)
	{
		if (one_arg(my_env) == -1)
			return (-1);
	}
	else if (tab[2] == NULL)
	{
		if (two_arg(my_env, tab, oldpwd) == -1)
			return (-1);
	}
	else
	{
		ft_puterr("cd: too many arguments\n");
		return (-1);
	}
	if ((setenv_push(my_env, "OLDPWD", oldpwd)) == -1)
		return (-1);
	return (0);
}

int			ft_cd(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7])
{
	char	oldpwd[4096 + 1];

	(void)dl;
	(void)ab;
	if (getcwd(oldpwd, 4096) == NULL)
	{
		ft_puterr("cd: permission denied: ");
		if (tab[0])
			ft_puterr(tab[1]);
		ft_puterr("\n");
		return (3);
	}
	if (check_arg(my_env, tab, oldpwd) == -1)
		return (3);
	if (getcwd(oldpwd, 4096) == NULL)
	{
		ft_puterr("cd: permission denied: ");
		if (tab[0])
			ft_puterr(tab[1]);
		ft_puterr("\n");
		return (3);
	}
	if ((setenv_push(my_env, "PWD", oldpwd)) == -1)
		return (-1);
	return (1);
}
