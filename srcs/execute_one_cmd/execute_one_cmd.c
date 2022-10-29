/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:39:05 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/26 19:24:12 by retcheba         ###   ########.fr       */
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
	if (cmd)
		free(cmd);
	cmd = NULL;
}

void	ft_execute_one_cmd(char **cmd, char **envp, int fd_in, int fd_out)
{
    char    *cmd_path;
    pid_t   pid;

	if (fd_in != -1)
	{
    	if (access(cmd[0], F_OK | X_OK) == 0)
		{
			cmd_path = cmd[0];
			cmd[0] = detach_cmd_from_path(cmd_path);
		}
		else
			cmd_path = get_cmd_path(cmd[0], envp);
		if (!cmd_path)
		{
			write(2, "Error: command not found\n", 25);
			ft_free_cmd(cmd_path, cmd);
		}
    	else
    	{
    	    pid = fork();
    	    if (pid == -1)
    	        perror("Error");
       		else if (pid == 0)
			{
            	if (fd_in != 0)
				{
					dup2(fd_in, 0);
					close(fd_in);
				}
				if (fd_out != 0)
				{
					dup2(fd_out, 1);
					close(fd_out);
				}
				execve(cmd_path, cmd, envp);
			}
			ft_free_cmd(cmd_path, cmd);
			if (fd_in != 0)
				close(fd_in);
			if (fd_out != 0)
				close(fd_out);
        	waitpid(pid, NULL, 0);
    	}
	}
}
