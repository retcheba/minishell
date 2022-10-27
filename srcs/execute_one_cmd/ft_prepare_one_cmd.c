/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_one_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 02:46:28 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/27 02:47:33 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int     ft_len_cmd(t_struct *mini)
{
    t_list  *begin;
    int len;

    len = 0;
    begin = mini->lst1;
    while (mini->lst1)
    {
        if (mini->lst1->tag == CMD)
        {
            len++;
            mini->lst1 = mini->lst1->next;
            while (mini->lst1 && mini->lst1->tag == ARG)
            {
                len++;
                mini->lst1 = mini->lst1->next;
            }
            break;
        }
        mini->lst1 = mini->lst1->next;
    }
    mini->lst1 = begin;
    return (len + 1);
}

int	ft_prepare_one_cmd(t_struct *mini, char **envp)
{
    int  i;
    char **cmd;
    int  len;
    t_list  *begin;

    len = ft_len_cmd(mini);
    cmd = malloc(sizeof(char *) * len);
    if (!cmd)
        return (1);
    cmd[len - 1] = NULL;
    i = 0;
    begin = mini->lst1;
    while (mini->lst1)
    {
        if (mini->lst1->tag == CMD)
        {
            cmd[i] = ft_substr(mini->lst1->content, 0, ft_strlen(mini->lst1->content));
            mini->lst1 = mini->lst1->next;
            while (mini->lst1 && mini->lst1->tag == ARG)
            {
                i++;
                cmd[i] = ft_substr(mini->lst1->content, 0, ft_strlen(mini->lst1->content));
                mini->lst1 = mini->lst1->next;
            }
            ft_execute_one_cmd(cmd, envp);
            break;
        }
        mini->lst1 = mini->lst1->next;
    }
    mini->lst1 = begin;
    return (0);
}
