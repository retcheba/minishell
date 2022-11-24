/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:14:03 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 03:57:40 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_nb_cmds(t_struct *mini)
{
	int		nb_cmds;
	t_list	*begin;

	nb_cmds = 1;
	begin = mini->lst1;
	while (mini->lst1)
	{
		if (mini->lst1->tag == PIPE)
			nb_cmds++;
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
	return (nb_cmds);
}

static int	fill_tab_fd_ios(t_struct *mini, t_pipex *pipex)
{
	t_list	*begin;
	int		index;
	int		error;

	error = 0;
	index = -1;
	while (index++ < pipex->nb_cmds - 1)
	{
		pipex->fd_ios[index] = NULL;
		pipex->fd_ios[index] = malloc(sizeof(**pipex->fd_ios) * 2);
	}
	index = 0;
	begin = mini->lst1;
	while (mini->lst1)
	{
		if (mini->lst1->tag == PIPE)
			mini->lst1 = mini->lst1->next;
		while (mini->lst1 && mini->lst1->tag != PIPE)
		{
			pipex->fd_ios[index][0] = 0;
			pipex->fd_ios[index][1] = 0;
			check_redirs(mini, &error, &pipex->fd_ios[index][0], &pipex->fd_ios[index][1]);
			while (mini->lst1 && mini->lst1->tag != PIPE)
				mini->lst1 = mini->lst1->next;
		}
		index++;
	}
	mini->lst1 = begin;
	return (error);
}

static char	***fill_tab_cmds(t_struct *mini, char ***cmds)
{
	t_list	*begin;
	int		index;

	index = 0;
	begin = mini->lst1;
	while (mini->lst1)
	{
		if (mini->lst1->tag == PIPE)
			mini->lst1 = mini->lst1->next;
		while (mini->lst1 && mini->lst1->tag != PIPE)
		{
			cmds[index] = ft_prepare_one_cmd(mini);
			while (mini->lst1 && mini->lst1->tag != PIPE)
				mini->lst1 = mini->lst1->next;
		}
		index++;
	}
	mini->lst1 = begin;
	return (cmds);
}

void	ft_prepare_pipex(t_struct *mini)
{
	char	***cmds;
	int		index;
	t_pipex	pipex;

	pipex.nb_cmds = ft_nb_cmds(mini);
	cmds = malloc((sizeof(char **)) * (pipex.nb_cmds + 1));
	if (!cmds)
		return ;
	cmds[pipex.nb_cmds] = NULL;
	pipex.fd_ios = NULL;
	pipex.fd_ios = malloc(sizeof(*pipex.fd_ios) * pipex.nb_cmds);
	fill_tab_fd_ios(mini, &pipex);
	cmds = fill_tab_cmds(mini, cmds);
	ft_pipex(&pipex, cmds, mini, pipex.fd_ios);
	free(cmds);
	index = 0;
	while (index < pipex.nb_cmds)
	{
		free(pipex.fd_ios[index]);
		index++;
	}
	free(pipex.fd_ios);
}
