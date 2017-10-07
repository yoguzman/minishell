/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguzman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 16:38:14 by yguzman           #+#    #+#             */
/*   Updated: 2017/09/28 12:52:39 by yguzman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "libft.h"

int		set_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (ft_puterr("tcgetattr fail in set_term\n"));
	term.c_lflag &= ~(ECHO | ICANON | ISIG | VINTR);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &term) == -1)
		return (ft_puterr("tcgetattr fail in set_term\n"));
	return (0);
}

int		unset_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (ft_puterr("tcgetattr fail in set_term\n"));
	term.c_lflag |= (ECHO | ICANON | ISIG | VINTR);
	if (tcsetattr(0, 0, &term) == -1)
		return (ft_puterr("tcgetattr fail in set_term\n"));
	return (0);
}
