/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tag_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:35:06 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/05 22:02:08 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tag_word(t_struct *mini)
{
	int	i;
	t_list	*begin;
	t_list	*copy;
	t_list	*ccopy;

	i = 0;
	begin = mini->lst1;
	copy = mini->lst1;
	ccopy = mini->lst1;
	while (mini->lst1)
	{
//		if (ft_strnstr(mini->tab[i], "$", ft_strlen(mini->tab[i])) != NULL)
//			mini->lst1->tag = $;
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
		else if (copy->tag == REDIR_IN || copy->tag == DREDIR_IN || copy->tag == REDIR_OUT || copy->tag == DREDIR_OUT)
			mini->lst1->tag = FILE;
		else if (i == 0 || copy->tag == PIPE)
		{
			if (/*ft_strstr(mini->tab[i], "echo") ||*/ ft_strstr(mini->tab[i], "cd")
				|| ft_strstr(mini->tab[i], "pwd") || ft_strstr(mini->tab[i], "export")
				|| ft_strstr(mini->tab[i], "unset") || ft_strstr(mini->tab[i], "env"))
				mini->lst1->tag = BUILTIN;
			else
				mini->lst1->tag = CMD;
		}
		else if (ccopy->tag == REDIR_IN || ccopy->tag == DREDIR_IN)
		{
			if (/*ft_strstr(mini->tab[i], "echo") ||*/ ft_strstr(mini->tab[i], "cd")
				|| ft_strstr(mini->tab[i], "pwd") || ft_strstr(mini->tab[i], "export")
				|| ft_strstr(mini->tab[i], "unset") || ft_strstr(mini->tab[i], "env"))
				mini->lst1->tag = BUILTIN;
			else
				mini->lst1->tag = CMD;
		}
		else
			mini->lst1->tag = ARG;
		mini->lst1 = mini->lst1->next;
		if (i != 0)
			copy = copy->next;
		if (i >= 2)
			ccopy = ccopy->next;
		i++;
	}
	mini->lst1 = begin;
	i = 0;
	/*while (mini->lst1)
	{
		printf("%d: word= %s  tag= %d\n", i, (char *)mini->lst1->content, mini->lst1->tag);
		mini->lst1 = mini->lst1->next;
		i++;
	}*/
	mini->lst1 = begin;
}
