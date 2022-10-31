/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds_multipipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:38:52 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/20 21:38:49 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void ft_execute_first_cmd(t_pipex *pipex, char ***cmds, char **envp)
{
	pid_t	pid;
	int	ok;

	pid = 0;
	ok = 0;
	if (pipe(pipex->fds_pipe1) != -1)
	{
		pipex->cmd = cmds[0];
		if (check_cmd(pipex, envp))
		{
			pid = fork();
			if (pid == -1)
				perror("Error");
			if (pid == 0)
			{
				dup2(pipex->fds_pipe1[1], 1);
				close(pipex->fds_pipe1[0]);
				close(pipex->fds_pipe1[1]);
				execve(pipex->cmd_path, pipex->cmd, envp);
			}
			ok = 1;
			ft_free_var(pipex->cmd_path, pipex->cmd);
		}
	}
	else
		perror("Error");
	pipex->pid = add_link_top(pipex->pid, &pid, ok);
}

static void ft_execute_even_cmd(t_pipex *pipex, char ***cmds, char **envp)
{
	pid_t	pid;
	int		ok;

	pid = 0;
	ok = 0;
	if (pipe(pipex->fds_pipe2) != -1)
	{
		pipex->cmd = cmds[pipex->index - 1];
		if (check_cmd(pipex, envp))
		{
			pid = fork();
			if (pid == -1)
				perror("Error");
			if (pid == 0)
			{
				dup2(pipex->fds_pipe1[0], 0);
				dup2(pipex->fds_pipe2[1], 1);
				close(pipex->fds_pipe1[0]);
				close(pipex->fds_pipe1[1]);
				close(pipex->fds_pipe2[0]);
				close(pipex->fds_pipe2[1]);
				execve(pipex->cmd_path, pipex->cmd, envp);
			}
			ok = 1;
			ft_free_var(pipex->cmd_path, pipex->cmd);
			close(pipex->fds_pipe1[0]);
			close(pipex->fds_pipe1[1]);	
		}
	}
	else
		perror("Error");
	pipex->pid = add_link_bottom(pipex->pid, new_link(&pid, ok));
}

static void ft_execute_odd_cmd(t_pipex *pipex, char ***cmds, char **envp)
{
	pid_t	pid;
	int		ok;

	pid = 0;
	ok = 0;
	if (pipe(pipex->fds_pipe1) != -1)
	{
		pipex->cmd = cmds[pipex->index - 1];
		if (check_cmd(pipex, envp))
		{
			pid = fork();
			if (pid == -1)
				perror("Error");
			if (pid == 0)
			{
				dup2(pipex->fds_pipe2[0], 0);
				dup2(pipex->fds_pipe1[1], 1);
				close(pipex->fds_pipe1[0]);
				close(pipex->fds_pipe1[1]);
				close(pipex->fds_pipe2[0]);
				close(pipex->fds_pipe2[1]);
				execve(pipex->cmd_path, pipex->cmd, envp);
			}
			ok = 1;
			ft_free_var(pipex->cmd_path, pipex->cmd);
			close(pipex->fds_pipe2[0]);
			close(pipex->fds_pipe2[1]);
		}
	}
	else
		perror("Error");
	pipex->pid = add_link_bottom(pipex->pid, new_link(&pid, ok));
}

static void ft_execute_last_cmd(t_pipex *pipex, char ***cmds, char **envp)
{
	pid_t	pid;
	int		ok;

	pid = 0;
	ok = 0;
	pipex->cmd = cmds[pipex->nb_cmds - 1];
	if (check_cmd(pipex, envp))
	{
		pid = fork();
		if (pid == -1)
			perror("Error");
		if (pid == 0)
		{
			if (pipex->nb_cmds % 2 == 0)
				dup2(pipex->fds_pipe1[0], 0);
			else
				dup2(pipex->fds_pipe2[0], 0);
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
			execve(pipex->cmd_path, pipex->cmd, envp);
		}
		ok = 1;
		ft_free_var(pipex->cmd_path, pipex->cmd);
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
	pipex->pid = add_link_bottom(pipex->pid, new_link(&pid, ok));
}

void	ft_execute_cmds_multipipe(t_pipex *pipex, char ***cmds, char **envp)
{
	t_list	*begin;

	pipex->pid = NULL;
	ft_execute_first_cmd(pipex, cmds, envp);
	pipex->index = 2;
	while (pipex->index < pipex->nb_cmds)
	{
		if (pipex->index % 2 == 0)
			ft_execute_even_cmd(pipex, cmds, envp);
		else
			ft_execute_odd_cmd(pipex, cmds, envp);
		pipex->index++;
	}
	ft_execute_last_cmd(pipex, cmds, envp);
	begin = pipex->pid;
	while (pipex->pid)
	{
		if (pipex->pid->tag == 1 && *(int *)pipex->pid->content != -1)
			waitpid(*(int *)pipex->pid->content, NULL, 0);
		pipex->pid = pipex->pid->next;
	}
	pipex->pid = begin;
	ft_free_list(pipex->pid);
}