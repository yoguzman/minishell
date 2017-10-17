/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:21:44 by yguzman           #+#    #+#             */
/*   Updated: 2017/10/09 13:24:34 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_H
# define MSH_H

# include <signal.h>
# include "libft.h"

# define BEGIN 0
# define LAST 1

typedef struct	s_data_line
{
	t_list		*cmd_hist;
	t_list		*comple_hist;
	int			pos_curs;
	char		buff[4];
	char		*line;
	int			ret_cmd;
}				t_dl;

typedef struct	s_array_bultin
{
	int			(*f)(t_list **my_env, char **tab, t_dl *dl,
						struct s_array_bultin *ab);
	char		*bultins;
}				t_ab;

typedef struct	s_array_key
{
	int			(*f)(t_dl *dl);
	char		buff[4];
}				t_ak;

t_list			*copy_env(char **env);
void			prompt_turfu(t_list *my_env);
int				exec_cmd(t_ab ab[7], t_dl *dl, t_list **my_env);
void			free_list(t_list *list);
void			catch_ctrlc();
void			free_tab(char **tab);
int				add_elem_to_env(t_list **my_env, char *add_env,
								int add_beg_or_last);
int				while_msh(t_list **my_env);
int				unset_term();
int				set_term();
int				edit_line(t_dl *dl, t_ak ak[6]);
int				init();
int				move_arrow_right(t_dl *dl);
int				move_arrow_left(t_dl *dl);
int				del_char(t_dl *dl);
void			init_ak(t_ak ak[5]);
int				ctrl_d(t_dl *dl);
int				new_line(t_dl *dl);
int				completion_down(t_dl *dl);
int				completion_up(t_dl *dl);
void			free_first_list(t_dl *dl);
int				ctrl_c(t_dl *dl);
int				init_ab(t_ab ab[7]);
int				ft_unsetenv(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7]);
int				ft_setenv(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7]);
int				ft_env(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7]);
int				ft_exit(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7]);
int				ft_cd(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7]);
int				ft_echo(t_list **my_env, char **tab, t_dl *dl, t_ab ab[7]);
void			free_ab(t_ab ab[7]);
int				setenv_push(t_list **my_env, char *var, char *word);
int				pos_eg(char *lol);
int				unsetenv_go(t_list **my_env, char *str);
int				exec(char *cmd, t_list **my_env, t_dl *dl, t_ab ab[7]);
int				tokenzer(char **line, t_list *my_env);
int				go_octal(char *str, int *ai);
int				equal(char *str);
t_list			*strdup_lst(t_list *my_env);
void			disp_env(t_list *tmp);
int				cpy_char(t_dl *dl);
void			move_l_or_r(int c_est_ma_direction);
void			free_char(char **str);
int				check_bultins(char **tab, t_ab ab[7], t_list **my_env,
								t_dl *dl);
int				exec_cmd_if_ok(char *path, char **tab, t_list *my_env,
								t_dl *dl);
int				find_path(char **path, t_list *my_env, t_dl *dl);
int				check_blank_line(char *line);
void			catch_segfault();
int				replace_tild(char **line, int *i, t_list *my_env);
int				free_home(char *home);

#endif
