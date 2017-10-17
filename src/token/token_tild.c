/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:37:44 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/09 13:23:35 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <stdlib.h>

void		end_replace_tild(char **line, char *buff, char *home)
{
	free(*line);
	if (buff)
		*line = buff;
	else
		*line = home;
}

char		*before_tild(char **line, int *i, char *home)
{
	char	*s1;
	char	*buff;

	s1 = NULL;
	buff = NULL;
	if ((s1 = malloc(sizeof(char) * (*i + 1))) == NULL)
		return (NULL);
	ft_strncpy(s1, *line, *i);
	s1[*i] = 0;
	if ((buff = ft_strjoin(s1, home)) == NULL)
		return (NULL);
	free(s1);
	free(home);
	return (buff);
}

int			after_tild(char *s2, char *buff, char **line)
{
	char	*s1;

	if ((s1 = ft_strjoin(buff, s2)) == NULL)
		return (-1);
	free(buff);
	free(s2);
	free(*line);
	*line = s1;
	return (0);
}

int			after_tild_if_no(char *s2, char *home, char *buff, char **line)
{
	if ((buff = ft_strjoin(home, s2)) == NULL)
		return (-1);
	free(home);
	free(s2);
	free(*line);
	*line = buff;
	return (0);
}

int			replace_tild(char **line, int *i, t_list *my_env)
{
	char	*s2;
	char	*buff;
	char	*home;

	home = ft_strdup(ft_getenv("HOME=", my_env));
	if (home == NULL || home[0] == 0)
		return (free_home(home));
	if ((buff = before_tild(line, i, home)) == NULL)
		return (-1);
	if ((int)(ft_strlen(*line) - 1) > *i)
	{
		if ((s2 = malloc(sizeof(char) * (*i + 1))) == NULL)
			return (-1);
		ft_strcpy(s2, (*line) + *i + 1);
		if (buff)
		{
			if (after_tild(s2, buff, line) == -1)
				return (-1);
			return (0);
		}
		if (after_tild_if_no(s2, home, buff, line) == -1)
			return (-1);
	}
	end_replace_tild(line, buff, home);
	return (0);
}
