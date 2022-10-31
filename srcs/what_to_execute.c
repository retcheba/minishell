/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_to_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 23:57:34 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/29 15:15:49 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	what_to_execute(t_struct *mini, char **envp)
{
    int pipex;
    int builtin;
    int cmd;
    t_list*begin;

    pipex = 0;
    builtin = 0;
    cmd = 0;
    begin = mini->lst1;
    while(mini->lst1)
    {
        if (mini->lst1->tag == PIPE)
            pipex++;
        if (mini->lst1->tag == BUILTIN)
            builtin++;
        if (mini->lst1->tag == CMD)
            cmd++;
        mini->lst1 = mini->lst1->next;
    }
    mini->lst1 = begin;
    if (pipex > 0)
        ft_prepare_pipex(mini, envp);
    else if (builtin > 0)
        ft_prepare_builtins(mini, envp);
    else if (cmd > 0)
        ft_prepare_one_cmd(mini, envp);
}
