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

static void	child_heredoc(char *stop, int fd_heredoc[2])
{
	char	*buff;

	buff = NULL;
	signal(SIGINT, sig_handler_heredoc);
	while (1 == 1)
	{
		buff = readline(">");
		if (buff == NULL)
		{
			printf("warning: here-document delimited by end-of-file\n");
			exit(1);
		}
		if (ft_strstr(buff, stop))
		{
			free(buff);
			exit(0);
		}
		ft_putendl_fd(buff, fd_heredoc[1]);
		free(buff);
	}
}

static void	sig_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGSEGV, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	sig_init(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

int	ft_heredoc(char *stop, int *value)
{
	pid_t	pid;
	int		fd_heredoc[2];
	int		status;

	status = 0;
	sig_ign();
	pipe(fd_heredoc);
	pid = fork();
	if (pid == -1)
		perror("Error");
	else if (pid == 0)
		child_heredoc(stop, fd_heredoc);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
				*value = WEXITSTATUS(status);
	sig_init();
	close (fd_heredoc[1]);
	if (*value == 1 || *value == 2)
	{
		close(fd_heredoc[0]);
		return (0);
	}
	return (fd_heredoc[0]);
}
