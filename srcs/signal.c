/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 05:41:43 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/19 05:42:14 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
sig=3 -> ^\
sig=2 -> ^C
sig=11 -> ^D
*/

void	sig_handler(int sig)
{
	if (sig == 11)
	{
		printf("exit\n");
		exit(g_status);
	}
	else if (sig == 2)
	{
		g_status = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	sig_handler_herdeoc(int sig)
{
	if (sig == 11)
	{
		printf("warning: here-document delimited by end-of-file\n");
		exit(0);
	}
	else if (sig == 2)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("\n", 0);
		exit(0);
	}
}
