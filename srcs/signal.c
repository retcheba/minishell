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

void	sig_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_init(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_child(void)
{
	signal(SIGINT, sig_handler_child);
	signal(SIGQUIT, sig_handler_child);
}

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
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig_handler_child(int sig)
{
	if (sig == 2)
	{
		printf("\n");
		g_status = 130;
	}
	else if (sig == 3)
	{
		printf("Quit (core dumped)\n");
		g_status = 130;
	}
}
