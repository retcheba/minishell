/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tag_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:35:06 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 03:08:14 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *str)
{
	if (ft_strstr(str, "echo")
		|| ft_strstr(str, "cd")
		|| ft_strstr(str, "pwd")
		|| ft_strstr(str, "export")
		|| ft_strstr(str, "unset")
		|| ft_strstr(str, "env"))
		return (1);
	return (0);
}

static int	is_builtin_or_cmd_before(t_list *begin, int i)
{
	int		cmd;
	t_list	*tmp;

	cmd = 0;
	tmp = begin;
	while (i-- > 0)
	{
		if (tmp->tag == CMD || tmp->tag == BUILTIN || tmp->tag == EXIT)
			cmd = 1;
		else if (tmp->tag == PIPE)
			cmd = 0;
		tmp = tmp->next;
	}
	return (cmd);
}

static int	is_first_tags(t_struct *mini, t_list *previous, int i)
{
	if (ft_strstr(mini->tab[i], "exit") && i == 0)
		mini->lst1->tag = EXIT;
	else if (ft_strstr(mini->tab[i], "|"))
		mini->lst1->tag = PIPE;
	else if (ft_strstr(mini->tab[i], "<"))
		mini->lst1->tag = REDIR_IN;
	else if (ft_strstr(mini->tab[i], ">"))
		mini->lst1->tag = REDIR_OUT;
	else if (ft_strstr(mini->tab[i], "<<"))
		mini->lst1->tag = DREDIR_IN;
	else if (ft_strstr(mini->tab[i], ">>"))
		mini->lst1->tag = DREDIR_OUT;
	else if (previous->tag == REDIR_IN || previous->tag == DREDIR_IN
		|| previous->tag == REDIR_OUT || previous->tag == DREDIR_OUT)
		mini->lst1->tag = FILE;
	else
		return (0);
	return (1);
}

static int	is_second_tags(t_struct *mini, t_list *begin, int i)
{
	if (!(is_builtin_or_cmd_before(begin, i)))
	{
		if (is_builtin(mini->tab[i]))
			mini->lst1->tag = BUILTIN;
		else
			mini->lst1->tag = CMD;
	}
	else
		return (0);
	return (1);
}

void	ft_tag_word(t_struct *mini)
{
	int		i;
	t_list	*begin;
	t_list	*previous;

	i = 0;
	begin = mini->lst1;
	previous = mini->lst1;
	while (mini->lst1)
	{
		if (!(is_first_tags(mini, previous, i)))
		{
			if (!(is_second_tags(mini, begin, i)))
				mini->lst1->tag = ARG;
		}
		mini->lst1 = mini->lst1->next;
		if (i != 0)
			previous = previous->next;
		i++;
	}
	mini->lst1 = begin;
}
