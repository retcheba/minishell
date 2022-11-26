/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 03:30:03 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/26 03:30:27 by retcheba         ###   ########.fr       */
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

int	check_cmd(char **cmd, char **cmd_path, char **envp)
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

void	ft_free_cmd(char *cmd_path, char **cmd)
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

int	check_builtins(char **cmd)
{
	if (ft_strstr(cmd[0], "echo") || ft_strstr(cmd[0], "cd")
		|| ft_strstr(cmd[0], "env") || ft_strstr(cmd[0], "export")
		|| ft_strstr(cmd[0], "unset") || ft_strstr(cmd[0], "pwd"))
		return (1);
	return (0);
}

void	print_execve_error(char *cmd_path)
{
	ft_putstr_fd(cmd_path, 2);
	ft_putstr_fd(": ", 2);
	if (access(cmd_path, F_OK | X_OK) == 0)
	{
		if ((cmd_path[0] == '.' && cmd_path[1] == '/')
			|| cmd_path[0] == '/')
			ft_putstr_fd(": Is a directory\n", 2);
		else
		{
			ft_putstr_fd("command not found\n", 2);
			exit (127);
		}
	}
	else if (((cmd_path[0] == '.' && cmd_path[1] == '/')
			|| cmd_path[0] == '/') && access(cmd_path, F_OK) != 0)
	{
		ft_putstr_fd("No such file or directory\n", 2);
		exit (127);
	}
	else
		perror("");
	exit(126);
}
