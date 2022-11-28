/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:29:11 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/26 01:30:40 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_redir_in(t_list **lst, int *error, int *fd_in)
{
	if ((*lst)->tag == REDIR_IN && (*lst)->next && (*lst)->next->tag == FILE)
	{
		*fd_in = open((*lst)->next->content, O_RDONLY);
		if (*fd_in == -1 && *error != 1)
		{
			ft_putstr_fd((*lst)->next->content, 2);
			ft_putstr_fd(": ", 2);
			perror("");
			*error = 1;
		}
	}
	if ((*lst)->tag == DREDIR_IN && (*lst)->next->tag == FILE)
		*fd_in = ft_heredoc((*lst)->next->content);
}

static void	check_redir_out(t_list **lst, int *error, int *fd_out)
{
	if ((*lst)->tag == REDIR_OUT && (*lst)->next->tag == FILE && *error != 1)
	{
		*fd_out = open((*lst)->next->content, O_WRONLY | O_TRUNC \
			| O_CREAT, 0644);
		if (*fd_out == -1 && *error != 1)
		{
			ft_putstr_fd((*lst)->next->content, 2);
			ft_putstr_fd(": ", 2);
			perror("");
			*error = 1;
		}
	}
	if ((*lst)->tag == DREDIR_OUT && (*lst)->next->tag == FILE && *error != 1)
	{
		*fd_out = open((*lst)->next->content, O_WRONLY | O_APPEND \
			| O_CREAT, 0644);
		if (*fd_out == -1 && *error != 1)
		{
			ft_putstr_fd((*lst)->next->content, 2);
			ft_putstr_fd(": ", 2);
			perror("");
			*error = 1;
		}
	}
}

void	check_redirs(t_struct *mini, int *error, int *fd_in, int *fd_out)
{
	t_list	*begin;
	int		fd_io[2];

	fd_io[0] = 0;
	fd_io[1] = 0;
	begin = mini->lst1;
	while (mini->lst1 && mini->lst1->tag != PIPE)
	{
		if (fd_in == NULL)
			check_redir_in(&mini->lst1, error, &fd_io[0]);
		else
			check_redir_in(&mini->lst1, error, fd_in);
		if (fd_out == NULL)
			check_redir_out(&mini->lst1, error, &fd_io[1]);
		else
			check_redir_out(&mini->lst1, error, fd_out);
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
	if (fd_io[0] != 0)
		close (fd_io[0]);
	if (fd_io[1] != 0)
		close (fd_io[1]);
}
