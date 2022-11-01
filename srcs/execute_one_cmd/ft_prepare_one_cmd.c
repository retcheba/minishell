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

static int  check_redir_in(t_struct *mini)
{
    int         fd_in;
    t_list    *begin;

    begin = mini->lst1;
    while (mini->lst1)
    {
        if (mini->lst1->tag == REDIR_IN && mini->lst1->next->tag == FILE)
        {
            fd_in = open(mini->lst1->next->content, O_RDONLY);
            if (fd_in == -1)
                perror("Error");
            mini->lst1 = begin;
            return(fd_in);
        }
        mini->lst1 = mini->lst1->next;
    }
    mini->lst1 = begin;
    return (0);
}

static int  check_redir_out(t_struct *mini)
{
    int         fd_out;
    t_list    *begin;

    fd_out = 0;
    begin = mini->lst1;
    while (mini->lst1)
    {
        if (mini->lst1->tag == REDIR_OUT && mini->lst1->next->tag == FILE)
        {
            fd_out = open(mini->lst1->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (fd_out == -1)
                perror("Error");
        }
        if (mini->lst1->tag == DREDIR_OUT && mini->lst1->next->tag == FILE)
        {
            fd_out = open(mini->lst1->next->content, O_WRONLY | O_APPEND |O_CREAT, 0644);
            if (fd_out == -1)
                perror("Error");
        }
        mini->lst1 = mini->lst1->next;
    }
    mini->lst1 = begin;
    return(fd_out);
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
            mini->lst1 = begin;
            ft_execute_one_cmd(cmd, envp, check_redir_in(mini), check_redir_out(mini));
            break;
        }
        mini->lst1 = mini->lst1->next;
    }
    mini->lst1 = begin;
    return (0);
}
