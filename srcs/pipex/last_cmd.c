/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:55:32 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/09 13:57:27 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_close_fds_pipe(t_pipex *pipex)
{
	if (pipex->nb_cmds % 2 == 0)
	{
		close(pipex->fds_pipe1[0]);
		close(pipex->fds_pipe1[1]);
	}
	else
	{
		close(pipex->fds_pipe2[0]);
		close(pipex->fds_pipe2[1]);
	}
}

static void	child(t_pipex *pipex, int fd_io[2], char **envp)
{
	if (fd_io[0] != 0)
	{
		dup2(fd_io[0], 0);
		close(fd_io[0]);
	}
	else
	{
		if (pipex->nb_cmds % 2 == 0)
			dup2(pipex->fds_pipe1[0], 0);
		else
			dup2(pipex->fds_pipe2[0], 0);
	}
	if (fd_io[1] != 0)
	{
		dup2(fd_io[1], 1);
		close(fd_io[1]);
	}
	ft_close_fds_pipe(pipex);
	execve(pipex->cmd_path, pipex->cmd, envp);
}

void	last_cmd(t_pipex *pipex, char ***cmds, char **envp, int fd_io[2])
{
	pid_t	pid;
	int		ok;

	pid = 0;
	ok = 0;
	pipex->cmd = cmds[pipex->nb_cmds - 1];
	if (check_cmd_pipex(pipex, envp) && fd_io[0] != -1)
	{
		pid = fork();
		if (pid == -1)
			perror("Error");
		if (pid == 0)
			child(pipex, fd_io, envp);
		ok = 1;
		ft_free_var(pipex->cmd_path, pipex->cmd);
		ft_close_fds_pipe(pipex);
		if (fd_io[0] != 0)
			close(fd_io[0]);
		if (fd_io[1] != 0)
			close(fd_io[1]);
		g_status = 0;
	}
	pipex->list = add_link_bottom_pipex(pipex->list, new_link_pipex(pid, ok));
}
