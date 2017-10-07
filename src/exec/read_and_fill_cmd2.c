/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_fill_cmd2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:37:39 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/28 14:26:34 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

char			**modif_env_char(t_list *my_env)
{
	t_list		*tmp;
	int			i;
	int			j;
	char		**tab;

	i = 0;
	if (my_env == NULL)
		return (NULL);
	tmp = my_env;
	while (tmp)
	{
		tmp = tmp->next;
		++i;
	}
	if ((tab = malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		tab[j] = my_env->content;
		my_env = my_env->next;
		++j;
	}
	tab[j] = NULL;
	return (tab);
}

int				error_exec_disp(char **tab)
{
	ft_puterr("msh: command not found: ");
	ft_puterr(tab[0]);
	ft_puterr("\n");
	return (-1);
}

int				exec_cmd_if_ok(char *path, char **tab, t_list *my_env, t_dl *dl)
{
	int			pid;
	int			status;
	char		**env_char;

	status = 0;
	env_char = modif_env_char(my_env);
	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
	{
		unset_term();
		if (execve(path, tab, env_char) == -1)
			return (error_exec_disp(tab));
		return (1);
	}
	else
	{
		if (wait(&status) == -1)
			return (-1);
	}
	set_term();
	status == 11 ? ft_putstr("Segmentation fault\n") : status == 11;
	dl->ret_cmd = (status == 0 ? 32 : 31);
	free(env_char);
	return (0);
}

int				check_bultins(char **tab, t_ab ab[7], t_list **my_env,
		t_dl *dl)
{
	int			i;
	int			ret;

	i = 0;
	while (ab[i].f)
	{
		if (ft_strcmp(ab[i].bultins, tab[0]) == 0)
		{
			ret = ab[i].f(my_env, tab, dl, ab);
			free_tab(tab);
			return (ret);
		}
		++i;
	}
	return (0);
}
