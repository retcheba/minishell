/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:38:52 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 04:16:25 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_execute_waitpid(t_pipex *pipex)
{
	t_pid	*begin;
	int		status;

	begin = pipex->list;
	while (pipex->list)
	{
		if (pipex->list->ok == 1)
		{
			if (pipex->list->pid != -1)
			{
				waitpid(pipex->list->pid, &status, 0);
				if (WIFEXITED(status) && pipex->list->next == NULL)
					g_status = WEXITSTATUS(status);
			}
		}
		pipex->list = pipex->list->next;
	}
	pipex->list = begin;
	ft_free_list_pipex(pipex->list);
}

void	ft_pipex(t_pipex *pipex, char ***cmds, t_struct *mini, int *fd_ios[2])
{
	pipex->list = NULL;
	first_cmd(pipex, cmds, mini, fd_ios[0]);
	pipex->index = 2;
	while (pipex->index < pipex->nb_cmds)
	{
		if (pipex->index % 2 == 0)
			even_cmd(pipex, cmds, mini, fd_ios[pipex->index - 1]);
		else
			odd_cmd(pipex, cmds, mini, fd_ios[pipex->index - 1]);
		pipex->index++;
	}
	last_cmd(pipex, cmds, mini, fd_ios[pipex->nb_cmds - 1]);
	ft_execute_waitpid(pipex);
}
