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

static int	is_syntax_error2(t_struct *mini)
{
	t_list	*begin;

	begin = mini->lst1;
	while (mini->lst1)
	{
		if (is_tag(mini->lst1->tag))
		{
			if (mini->lst1->next == NULL)
			{
				ft_putstr_fd("syntax error near unexpected token\n", 2);
				mini->lst1 = begin;
				return (1);
			}
			else if (is_tag(mini->lst1->next->tag))
			{
				ft_putstr_fd("syntax error near unexpected token\n", 2);
				mini->lst1 = begin;
				return (1);
			}
		}
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
	return (0);
}

static int	is_syntax_error(t_struct *mini)
{
	t_list	*begin;

	if (mini->lst1->tag == PIPE && mini->lst1->next != NULL)
	{
		if (mini->lst1->next->tag != PIPE)
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			return (1);
		}
	}
	begin = mini->lst1;
	while (mini->lst1)
	{
		if (!is_tag(mini->lst1->tag) && check_content(mini->lst1->content))
		{
			ft_putstr_fd("syntax error near unexpected token\n", 2);
			mini->lst1 = begin;
			return (1);
		}
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
	if (is_syntax_error2(mini))
		return (1);
	return (0);
}

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

void	what_to_execute(t_struct *mini)
{
	int		pipex;
	int		builtin;
	int		cmd;
	int		error;

	pipex = 0;
	builtin = 0;
	cmd = 0;
	error = 0;
	if (!(is_syntax_error(mini)))
	{
		check_what(mini, &pipex, &builtin, &cmd);
		if (pipex > 0)
			ft_prepare_pipex(mini);
		else if (builtin > 0 || cmd > 0)
			ft_prepare_simple_cmd(mini);
		else
		{
			check_redirs(mini, &error, NULL, NULL);
			if (error == 1)
				g_status = 1;
		}
	}
	else
		g_status = 2;
}
