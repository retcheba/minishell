/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:16:56 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 05:15:32 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc(char *stop)
{
	pid_t	pid;
	int		fd_heredoc[2];
	char	*buff;

	buff = NULL;
	signal(SIGINT, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (pipe(fd_heredoc) != -1)
	{
		pid = fork();
		if (pid == -1)
			perror("Error");
		else if (pid == 0)
		{
			signal(SIGINT, sig_handler_heredoc);
			signal(SIGSEGV, sig_handler_heredoc);
			signal(SIGQUIT, SIG_IGN);
			while (1 == 1)
			{
				buff = readline(">");
				if (ft_strstr(buff, stop))
				{
					free(buff);
					exit(0);
				}
				ft_putendl_fd(buff, fd_heredoc[1]);
				free(buff);
			}
			
		}
		waitpid(pid, NULL, 0);
		
	}
	else
	{
		perror("Error");
		return (-1);
	}
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	close (fd_heredoc[1]);
	return (fd_heredoc[0]);
}
