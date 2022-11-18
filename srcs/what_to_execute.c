/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_to_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 23:57:34 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 04:10:49 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_what(t_struct *mini, int	*pipex, int	*builtin, int *cmd)
{
	t_list	*begin;

	begin = mini->lst1;
	while (mini->lst1)
	{
		if (mini->lst1->tag == PIPE)
			*pipex += 1;
		if (mini->lst1->tag == BUILTIN)
			*builtin += 1;
		if (mini->lst1->tag == CMD)
			*cmd += 1;
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
}

void	what_to_execute(t_struct *mini, char **envp)
{
	int		pipex;
	int		builtin;
	int		cmd;

	pipex = 0;
	builtin = 0;
	cmd = 0;
	if (1 == 1)
	{
		check_what(mini, &pipex, &builtin, &cmd);
		if (pipex > 0)
			ft_prepare_pipex(mini, envp);
		else if (builtin > 0)
			ft_prepare_builtins(mini);
		else if (cmd > 0)
			ft_prepare_simple_cmd(mini, envp);
		else
			check_redir_in(mini);
	}
}
