/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 04:29:12 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 04:15:15 by retcheba         ###   ########.fr       */
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

int	check_cmd_pipex(t_pipex *pipex, char **envp)
{
	if (access(pipex->cmd[0], F_OK | X_OK) == 0)
	{
		pipex->cmd_path = pipex->cmd[0];
		pipex->cmd[0] = detach_cmd_from_path(pipex->cmd_path);
	}
	else
		pipex->cmd_path = get_cmd_path(pipex->cmd[0], envp);
	if (!pipex->cmd_path)
	{
		write(2, pipex->cmd[0], ft_strlen(pipex->cmd[0]));
		write(2, ": command not found\n", 20);
		g_status = 127;
		ft_free_var(pipex->cmd_path, pipex->cmd);
		return (0);
	}
	return (1);
}
