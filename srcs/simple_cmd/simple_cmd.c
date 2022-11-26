/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:39:05 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 04:51:04 by retcheba         ###   ########.fr       */
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

static void	exec_builtin(t_struct *mini, char **cmd, int fd_io[2])
{
	int	cpy[2];

	if (fd_io[0] != 0)
	{
		cpy[0] = dup(0);
		dup2(fd_io[0], 0);
	}
	if (fd_io[1] != 0)
	{
		cpy[1] = dup(1);
		dup2(fd_io[1], 1);
	}
	ft_prepare_builtins(mini, cmd);
	if (fd_io[0] != 0)
	{
		close(fd_io[0]);
		dup2(cpy[0], 0);
		close(cpy[0]);
	}
	if (fd_io[1] != 0)
	{
		close(fd_io[1]);
		dup2(cpy[1], 1);
		close(cpy[1]);
	}
}

static void	child_execve(char **envp, char **cmd, char *cmd_path, int fd_io[2])
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
	if (execve(cmd_path, cmd, envp) == -1)
		print_execve_error(cmd_path);
}

void	simple_cmd(t_struct *mini, char **cmd, int fd_io[2], int error)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	status = 0;
	cmd_path = NULL;
	if (fd_io[0] != -1 && fd_io[1] != -1 && error != 1)
	{
		if (check_builtins(cmd))
			exec_builtin(mini, cmd, fd_io);
		else if (check_cmd(cmd, &cmd_path, mini->envp))
		{
			pid = fork();
			if (pid == -1)
				perror("Error");
			else if (pid == 0)
				child_execve(mini->envp, cmd, cmd_path, fd_io);
			ft_close_fd_io(fd_io);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
					g_status = WEXITSTATUS(status);
		}
	}
	ft_free_cmd(cmd_path, cmd);
}
