/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tag_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:35:06 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/26 16:25:27 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tag_word(t_struct *mini)
{
	int	i;
	t_list	*begin;
	t_list	*copy;

	i = 0;
	begin = mini->lst1;
	copy = mini->lst1;
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
		else if (copy->tag == REDIR_IN || copy->tag == REDIR_OUT || copy->tag == DREDIR_OUT)
			mini->lst1->tag = FILE;
		else if (i == 0 || copy->tag == PIPE)
			mini->lst1->tag = CMD;
		else
		{
			mini->lst1->tag = ARG;
		}
		if (i >= 2)
		{
			if (ft_strstr(mini->tab[i - 2], "<"))
				mini->lst1->tag = CMD;
		}
		mini->lst1 = mini->lst1->next;
		if (i != 0)
			copy = copy->next;
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
