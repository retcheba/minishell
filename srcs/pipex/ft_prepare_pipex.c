/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 18:14:03 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/30 18:14:05 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  check_redir_in(t_struct *mini)
{
    int         fd_in;
    t_list    *begin;

    begin = mini->lst1;
    while (mini->lst1 && mini->lst1->tag != PIPE)
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

    begin = mini->lst1;
    while (mini->lst1 && mini->lst1->tag != PIPE)
    {
        if (mini->lst1->tag == REDIR_OUT && mini->lst1->next->tag == FILE)
        {
            fd_out = open(mini->lst1->next->content, O_WRONLY | O_TRUNC | O_CREAT, 0644);
            if (fd_out == -1)
                perror("Error");
            mini->lst1 = begin;
            return(fd_out);
        }
        mini->lst1 = mini->lst1->next;
    }
    mini->lst1 = begin;
    return (0);
}

static char **ft_prepare_cmd(t_struct *mini)
{
    char **cmd;
    t_list  *begin;
    int     i;

    begin = mini->lst1;
    i = 0;
    while (mini->lst1 && mini->lst1->tag != PIPE)
    {
        if (mini->lst1->tag == CMD)
        {
            i++;
            mini->lst1 = mini->lst1->next;
            while (mini->lst1 && mini->lst1->tag == ARG)
            {
                i++;
                mini->lst1 = mini->lst1->next;
            }
            break;
        }
        mini->lst1 = mini->lst1->next;
    }
    mini->lst1 = begin;
    cmd = malloc(sizeof(char *) * (i + 1));
    if (!cmd)
        return(NULL);
    cmd[i] = NULL;
    i = 0;
    while (mini->lst1 && mini->lst1->tag != PIPE)
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
            break;
        }
        mini->lst1 = mini->lst1->next;
    }
    mini->lst1 = begin;
    return (cmd);
}

void	ft_prepare_pipex(t_struct *mini, char **envp)
{
    char    ***cmds;
    int     **fd_ios;
    int     index;
    t_list *begin;
    t_pipex pipex;

    pipex.nb_cmds = 1;
    begin = mini->lst1;
    while (mini->lst1)
    {
        if (mini->lst1->tag == PIPE)
            pipex.nb_cmds++;
        mini->lst1 = mini->lst1->next;
    }
    cmds = malloc((sizeof(char **)) * (pipex.nb_cmds + 1));
    if (!cmds)
        return ;
    cmds[pipex.nb_cmds] = NULL;
    fd_ios = NULL;
    fd_ios = malloc(sizeof(*fd_ios) * pipex.nb_cmds);
    index = 0;
    while (index < pipex.nb_cmds)
    {
        fd_ios[index] = NULL;
        fd_ios[index] = malloc(sizeof(**fd_ios) * 2);
        index++;
    }
    mini->lst1 = begin;
    index = 0;
    while (mini->lst1)
    {
        if (mini->lst1->tag == PIPE)
            mini->lst1 = mini->lst1->next;
        while (mini->lst1 && mini->lst1->tag != PIPE)
        {
            cmds[index] = ft_prepare_cmd(mini);
            fd_ios[index][0] = check_redir_in(mini);
            fd_ios[index][1] = check_redir_out(mini);
            while (mini->lst1 && mini->lst1->tag != PIPE)
                mini->lst1 = mini->lst1->next;
        }
        index++;
    }
    mini->lst1 = begin;
    ft_execute_cmds_multipipe(&pipex, cmds, envp, fd_ios);
    free(cmds);
    index = 0;
    while (index < pipex.nb_cmds)
    {
        free(fd_ios[index]);
        index++;
    }
    free(fd_ios);
}