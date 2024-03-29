/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_simple_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 02:46:28 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 05:10:34 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_len_cmd(t_struct *mini)
{
	t_list	*begin;
	int		len;

	len = 0;
	begin = mini->lst1;
	while (mini->lst1)
	{
		if (mini->lst1->tag == CMD || mini->lst1->tag == BUILTIN)
		{
			len++;
			mini->lst1 = mini->lst1->next;
			while (mini->lst1)
			{
				if (mini->lst1->tag == ARG)
					len++;
				mini->lst1 = mini->lst1->next;
			}
			break ;
		}
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
	return (len + 1);
}

static void	fill_cmd(t_struct *mini, char **cmd, int *i)
{
	cmd[*i] = ft_substr(mini->lst1->content, 0, \
		ft_strlen(mini->lst1->content));
	*i += 1;
}

static char	**fill_tab_cmd(t_struct *mini, char **cmd)
{
	int		i;
	t_list	*begin;

	i = 0;
	begin = mini->lst1;
	while (mini->lst1)
	{
		if (mini->lst1->tag == CMD || mini->lst1->tag == BUILTIN)
		{
			fill_cmd(mini, cmd, &i);
			mini->lst1 = mini->lst1->next;
			while (mini->lst1)
			{
				if (mini->lst1->tag == ARG)
					fill_cmd(mini, cmd, &i);
				mini->lst1 = mini->lst1->next;
			}
			break ;
		}
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
	return (cmd);
}

int	ft_prepare_simple_cmd(t_struct *mini)
{
	char	**cmd;
	int		fd_io[2];
	int		len;
	int		error;

	error = 0;
	fd_io[0] = 0;
	fd_io[1] = 0;
	len = ft_len_cmd(mini);
	cmd = malloc(sizeof(char *) * len);
	if (!cmd)
		return (1);
	cmd[len - 1] = NULL;
	cmd = fill_tab_cmd(mini, cmd);
	check_redirs(mini, &error, &fd_io[0], &fd_io[1]);
	simple_cmd(mini, cmd, fd_io, error);
	sig_init();
	if (error == 1)
		g_status = 1;
	return (0);
}
