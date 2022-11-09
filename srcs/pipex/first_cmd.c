/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:49:59 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/09 13:50:46 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_close_fd_io(int fd_io[2])
{
	if (fd_io[0] != 0)
		close(fd_io[0]);
	if (fd_io[1] != 0)
		close(fd_io[1]);
}

static void	child(t_pipex *pipex, int fd_io[2], char **envp)
{
	if (fd_io[0] != 0)
	{
		dup2(fd_io[0], 0);
		close(fd_io[0]);
	}
	if (fd_io[1] != 0)
	{
		dup2(fd_io[1], 1);
		close(fd_io[1]);
	}
	else
		dup2(pipex->fds_pipe1[1], 1);
	close(pipex->fds_pipe1[0]);
	close(pipex->fds_pipe1[1]);
	execve(pipex->cmd_path, pipex->cmd, envp);
}

void	first_cmd(t_pipex *pipex, char ***cmds, char **envp, int fd_io[2])
{
	pid_t	pid;
	int		ok;

	pid = 0;
	ok = 0;
	if (pipe(pipex->fds_pipe1) != -1)
	{
		pipex->cmd = cmds[0];
		if (check_cmd_pipex(pipex, envp) && fd_io[0] != -1)
		{
			pid = fork();
			if (pid == -1)
				perror("Error");
			if (pid == 0)
				child(pipex, fd_io, envp);
			ok = 1;
			ft_free_var(pipex->cmd_path, pipex->cmd);
			ft_close_fd_io(fd_io);
		}
	}
	else
		perror("Error");
	pipex->list = add_link_top_pipex(pipex->list, pid, ok);
}
