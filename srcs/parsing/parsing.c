/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:11:21 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/26 16:11:25 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parsing(t_struct *mini)
{
	int		i;

	mini->tab = ft_split_minishell(mini->buff, ' ');
	mini->lst1 = NULL;
	i = 0;
	while (mini->tab[i])
	{
		if (mini->lst1 == NULL)
			mini->lst1 = new_link(mini->tab[i], -1);
		else
			add_link_bottom(mini->lst1, new_link(mini->tab[i], -1));
		i++;
	}
}
