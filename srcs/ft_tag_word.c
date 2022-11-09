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
	if (
		//ft_strstr(mini->tab[i], "echo") ||
		ft_strstr(str, "cd")
		|| ft_strstr(str, "pwd")
		|| ft_strstr(str, "export")
		|| ft_strstr(str, "unset")
		|| ft_strstr(str, "env"))
		return (1);
	return (0);
}

static int	is_first_tags(t_struct *mini, t_list *copy, int i)
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
	else if (copy->tag == REDIR_IN || copy->tag == DREDIR_IN
		|| copy->tag == REDIR_OUT || copy->tag == DREDIR_OUT)
		mini->lst1->tag = FILE;
	else
		return (0);
	return (1);
}

static int	is_second_tags(t_struct *mini, t_list *copy, t_list *ccopy, int i)
{
	if (i == 0 || copy->tag == PIPE)
	{
		if (is_builtin(mini->tab[i]))
			mini->lst1->tag = BUILTIN;
		else
			mini->lst1->tag = CMD;
	}
	else if (ccopy->tag == REDIR_IN || ccopy->tag == DREDIR_IN)
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
	t_list	*copy;
	t_list	*ccopy;

	i = 0;
	begin = mini->lst1;
	copy = mini->lst1;
	ccopy = mini->lst1;
	while (mini->lst1)
	{
		if (!(is_first_tags(mini, copy, i)))
		{
			if (!(is_second_tags(mini, copy, ccopy, i)))
				mini->lst1->tag = ARG;
		}
		mini->lst1 = mini->lst1->next;
		if (i != 0)
			copy = copy->next;
		if (i >= 2)
			ccopy = ccopy->next;
		i++;
	}
	mini->lst1 = begin;
}

/*
	i = 0;
	while (mini->lst1)
	{
		printf("%d: word= %s  tag= %d\n", i, 
			(char *)mini->lst1->content, mini->lst1->tag);
		mini->lst1 = mini->lst1->next;
		i++;
	}
	mini->lst1 = begin;
*/