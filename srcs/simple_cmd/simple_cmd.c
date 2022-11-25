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

static int	check_builtins(char **cmd)
{
	if (ft_strstr(cmd[0], "echo") || ft_strstr(cmd[0], "cd")
		|| ft_strstr(cmd[0], "env") || ft_strstr(cmd[0], "export")
		|| ft_strstr(cmd[0], "unset") || ft_strstr(cmd[0], "pwd"))
		return (1);
	return (0);
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
		if (cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
		{
			*cmd_path = ft_strdup(cmd[0]);
			return (1);
		}
		else
		{
			write(2, cmd[0], ft_strlen(cmd[0]));
			write(2, ": command not found\n", 20);
		}
		g_status = 127;
		return (0);
	}
	return (1);
}

static void	exec_builtin(t_struct *mini, char **cmd, int fd_io[2])
{
	int	cpy0;
	int	cpy1;

	if (fd_io[0] != 0)
	{
		cpy0 = dup(0);
		dup2(fd_io[0], 0);
	}
	if (fd_io[1] != 0)
	{
		cpy1 = dup(1);
		dup2(fd_io[1], 1);
	}
	ft_prepare_builtins(mini, cmd);
	if (fd_io[0] != 0)
	{
		close(fd_io[0]);
		dup2(cpy0, 0);
		close(cpy0);
	}
	if (fd_io[1] != 0)
	{
		close(fd_io[1]);
		dup2(cpy1, 1);
		close(cpy1);
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
	{
		ft_putstr_fd(cmd_path, 2);
		ft_putstr_fd(": ", 2);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			if ((cmd_path[0] == '.' && cmd_path[1] == '/') || cmd_path[0] == '/')
				ft_putstr_fd(": Is a directory\n", 2);
			else
			{
				ft_putstr_fd("command not found\n", 2);
				exit (127);
			}
		}
		else if (((cmd_path[0] == '.' && cmd_path[1] == '/') || cmd_path[0] == '/')
			&& access(cmd_path, F_OK) != 0)
		{
			ft_putstr_fd("No such file or directory\n", 2);
			exit (127);
		}
		else
			perror("");
		exit(126);
	}
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
			if (fd_io[0] != 0)
				close(fd_io[0]);
			if (fd_io[1] != 0)
				close(fd_io[1]);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
					g_status = WEXITSTATUS(status);
		}
	}
	ft_free_cmd(cmd_path, cmd);
}
