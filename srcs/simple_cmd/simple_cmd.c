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

static char	*detach_cmd_from_path(char *cmd_path)
{
	char	*cmd;
	int		start;
	int		len;

	start = 0;
	len = 0;
	while (cmd_path[start + 1])
		start++;
	while (cmd_path[start] != '/' && start != 0)
	{
		len++;
		start--;
	}
	cmd = ft_substr(cmd_path, start, len);
	return (cmd);
}

static void	ft_free_cmd(char *cmd_path, char **cmd)
{
	int	i;

	if (cmd_path)
		free(cmd_path);
	cmd_path = NULL;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		cmd[i] = NULL;
		i++;
	}
	free(cmd);
	cmd = NULL;
}

static int	check_cmd(char **cmd, char **cmd_path, char **envp)
{
	if (access(cmd[0], F_OK | X_OK) == 0)
	{
		*cmd_path = cmd[0];
		cmd[0] = detach_cmd_from_path(*cmd_path);
	}
	else
		*cmd_path = get_cmd_path(cmd[0], envp);
	if (!(*cmd_path))
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 20);
		g_status = 127;
		return (0);
	}
	return (1);
}

static void	child(char **envp, char **cmd, char *cmd_path, int fd_io[2])
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
	execve(cmd_path, cmd, envp);
}

void	simple_cmd(char **cmd, char **envp, int fd_io[2])
{
	char	*cmd_path;
	pid_t	pid;

	cmd_path = NULL;
	if (fd_io[0] != -1)
	{
		if (check_cmd(cmd, &cmd_path, envp))
		{
			pid = fork();
			if (pid == -1)
				perror("Error");
			else if (pid == 0)
				child(envp, cmd, cmd_path, fd_io);
			if (fd_io[0] != 0)
				close(fd_io[0]);
			if (fd_io[1] != 0)
				close(fd_io[1]);
			waitpid(pid, NULL, 0);
			g_status = 0;
		}
	}
	ft_free_cmd(cmd_path, cmd);
}
