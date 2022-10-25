/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tag_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:35:06 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/25 16:33:57 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_tag_word(t_struct *mini)
{
	int	i;
	t_list	*begin;

	i = 0;
	begin = mini->lst1;
	while (mini->lst1)
	{
		if (ft_strncmp((char *)mini->lst1->content, "exit", ft_strlen((char *)mini->lst1->content)) == 0
			&& ft_strlen((char *)mini->lst1->content) != 0 && i == 0)
				mini->lst1->tag = EXIT;
		mini->lst1 = mini->lst1->next;
		i++;
	}
	mini->lst1 = begin;
	i = 0;
	while (mini->lst1)
	{
		printf("%d: word=%s tag=%d\n", i, (char *)mini->lst1->content, mini->lst1->tag);
		mini->lst1 = mini->lst1->next;
		i++;
	}
	mini->lst1 = begin;
}
