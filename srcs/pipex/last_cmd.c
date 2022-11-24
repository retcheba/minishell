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

static void	child_builtin(t_pipex *pipex, int fd_io[2], t_struct *mini)
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
	ft_prepare_builtins(mini, pipex->cmd);
	ft_free_tab(pipex->cmd);
	exit(g_status);
}

static void	child_execve(t_pipex *pipex, int fd_io[2], char **envp)
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

void	last_cmd(t_pipex *pipex, char ***cmds, t_struct *mini, int fd_io[2])
{
	pid_t	pid;
	int		ok;

	pid = 0;
	ok = 0;
	pipex->cmd = cmds[pipex->nb_cmds - 1];
	if (check_builtins_pipex(pipex) && fd_io[0] != -1 && fd_io[1] != -1)
	{
		pid = fork();
		if (pid == -1)
			perror("Error");
		if (pid == 0)
			child_builtin(pipex, fd_io, mini);
		ok = 1;
		ft_free_tab(pipex->cmd);
		ft_close_fds_pipe(pipex);
		if (fd_io[0] != 0)
			close(fd_io[0]);
		if (fd_io[1] != 0)
			close(fd_io[1]);
	}
	else if (check_cmd_pipex(pipex, mini->envp) && fd_io[0] != -1 && fd_io[1] != -1)
	{
		pid = fork();
		if (pid == -1)
			perror("Error");
		if (pid == 0)
			child_execve(pipex, fd_io, mini->envp);
		ok = 1;
		ft_free_var(pipex->cmd_path, pipex->cmd);
		ft_close_fds_pipe(pipex);
		if (fd_io[0] != 0)
			close(fd_io[0]);
		if (fd_io[1] != 0)
			close(fd_io[1]);
	}
	else
		g_status = 1;
	pipex->list = add_link_bottom_pipex(pipex->list, new_link_pipex(pid, ok));
}
