/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_fill_cmd1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:42:02 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/27 16:44:28 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <unistd.h>

int				check_blank_line(char *line)
{
	char		*tmp;

	tmp = line;
	if (line == NULL)
		return (1);
	while (*line)
	{
		if (ft_isspace(*line) == 0)
			return (0);
		++line;
	}
	return (1);
}

char			*check_last_char(char *str)
{
	int			i;
	char		*new;

	i = ft_strlen(str) - 1;
	if (i == -1)
		i = 0;
	if (str[i] != '/')
	{
		if ((new = ft_strjoin(str, "/")) == NULL)
			return (NULL);
	}
	else
	{
		if ((new = ft_strdup(str)) == NULL)
			return (NULL);
	}
	return (new);
}

char			*create_new_path(char *diff_path, char *path)
{
	char		*test;
	char		*test_path;

	test = check_last_char(diff_path);
	if ((test_path = ft_strjoin(test, path)) == NULL)
		return (NULL);
	free(test);
	return (test_path);
}

int				check_path(char *test_path, char **path, t_dl *dl)
{
	dl->ret_cmd = -1;
	if ((*path)[0] == '/')
		if (access(*path, F_OK) == 0)
		{
			if (access(*path, X_OK) == 0)
			{
				free(test_path);
				return (2);
			}
			free(test_path);
			return (-2);
		}
	if (access(test_path, F_OK) == 0)
	{
		if (access(test_path, X_OK) == 0)
		{
			free(*path);
			*path = test_path;
			return (1);
		}
		free(test_path);
		return (-2);
	}
	free(test_path);
	return (0);
}

int				find_path(char **path, t_list *my_env, t_dl *dl)
{
	char		*var_path;
	char		**diff_path;
	char		*test_path;
	int			i;
	int			ret;

	if ((var_path = ft_getenv("PATH=", my_env)) == NULL)
		return (1);
	if ((diff_path = ft_strsplit(var_path, ":")) == NULL)
		return (ft_puterr("strsplit fail in read and fill cmd\n"));
	i = 0;
	while (diff_path[i])
	{
		if ((test_path = create_new_path(diff_path[i], *path)) == NULL)
			return (-1);
		if ((ret = check_path(test_path, path, dl)) != 0)
			break ;
		++i;
	}
	if (ret == 1 && *path != test_path)
		free_char(path);
	free_tab(diff_path);
	if (ret == -2)
		return (ret);
	return (0);
}
