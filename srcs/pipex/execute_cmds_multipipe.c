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

static void ft_execute_first_cmd(t_pipex *pipex, char ***cmds, char **envp, int fd_io[2])
{
	pid_t	pid;
	int	ok;

	pid = 0;
	ok = 0;
	if (pipe(pipex->fds_pipe1) != -1)
	{
		pipex->cmd = cmds[0];
		if (check_cmd(pipex, envp) && fd_io[0] != -1)
		{
			pid = fork();
			if (pid == -1)
				perror("Error");
			if (pid == 0)
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
			ok = 1;
			ft_free_var(pipex->cmd_path, pipex->cmd);
			if (fd_io[0] != 0)
				close(fd_io[0]);
			if (fd_io[1] != 0)
				close(fd_io[1]);
		}
	}
	else
		perror("Error");
	pipex->list = add_link_top_pipex(pipex->list, pid, ok);
}

static void ft_execute_even_cmd(t_pipex *pipex, char ***cmds, char **envp, int fd_io[2])
{
	pid_t	pid;
	int		ok;

	pid = 0;
	ok = 0;
	if (pipe(pipex->fds_pipe2) != -1)
	{
		pipex->cmd = cmds[pipex->index - 1];
		if (check_cmd(pipex, envp) && fd_io[0] != -1)
		{
			pid = fork();
			if (pid == -1)
				perror("Error");
			if (pid == 0)
			{
				if (fd_io[0] != 0)
				{
					dup2(fd_io[0], 0);
					close(fd_io[0]);
				}
				else
					dup2(pipex->fds_pipe1[0], 0);
				if (fd_io[1] != 0)
				{
					dup2(fd_io[1], 1);
					close(fd_io[1]);
				}
				else
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
			if (fd_io[0] != 0)
				close(fd_io[0]);
			if (fd_io[1] != 0)
				close(fd_io[1]);
		}
	}
	else
		perror("Error");
	pipex->list = add_link_bottom_pipex(pipex->list, new_link_pipex(pid, ok));
}

static void ft_execute_odd_cmd(t_pipex *pipex, char ***cmds, char **envp, int fd_io[2])
{
	pid_t	pid;
	int		ok;

	pid = 0;
	ok = 0;
	if (pipe(pipex->fds_pipe1) != -1)
	{
		pipex->cmd = cmds[pipex->index - 1];
		if (check_cmd(pipex, envp) && fd_io[0] != -1)
		{
			pid = fork();
			if (pid == -1)
				perror("Error");
			if (pid == 0)
			{
				if (fd_io[0] != 0)
				{
					dup2(fd_io[0], 0);
					close(fd_io[0]);
				}
				else
					dup2(pipex->fds_pipe2[0], 0);
				if (fd_io[1] != 0)
				{
					dup2(fd_io[1], 1);
					close(fd_io[1]);
				}
				else
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
			if (fd_io[0] != 0)
				close(fd_io[0]);
			if (fd_io[1] != 0)
				close(fd_io[1]);
		}
	}
	else
		perror("Error");
	pipex->list = add_link_bottom_pipex(pipex->list, new_link_pipex(pid, ok));
}

static void ft_execute_last_cmd(t_pipex *pipex, char ***cmds, char **envp, int fd_io[2])
{
	pid_t	pid;
	int		ok;

	pid = 0;
	ok = 0;
	pipex->cmd = cmds[pipex->nb_cmds - 1];
	if (check_cmd(pipex, envp) && fd_io[0] != -1)
	{
		pid = fork();
		if (pid == -1)
			perror("Error");
		if (pid == 0)
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
		if (fd_io[0] != 0)
			close(fd_io[0]);
		if (fd_io[1] != 0)
			close(fd_io[1]);
	}
	pipex->list = add_link_bottom_pipex(pipex->list, new_link_pipex(pid, ok));
}

void	ft_execute_cmds_multipipe(t_pipex *pipex, char ***cmds, char **envp, int *fd_ios[2])
{
	t_pid	*begin;

	pipex->list = NULL;
	ft_execute_first_cmd(pipex, cmds, envp, fd_ios[0]);
	pipex->index = 2;
	while (pipex->index < pipex->nb_cmds)
	{
		if (pipex->index % 2 == 0)
			ft_execute_even_cmd(pipex, cmds, envp, fd_ios[pipex->index - 1]);
		else
			ft_execute_odd_cmd(pipex, cmds, envp, fd_ios[pipex->index - 1]);
		pipex->index++;
	}
	ft_execute_last_cmd(pipex, cmds, envp, fd_ios[pipex->nb_cmds - 1]);
	begin = pipex->list;
	while (pipex->list)
	{
		if (pipex->list->ok == 1)
		{
			if (pipex->list->pid != -1)
				waitpid(pipex->list->pid, NULL, 0);
		}
		pipex->list = pipex->list->next;
	}
	pipex->list = begin;
	ft_free_list_pipex(pipex->list);
}