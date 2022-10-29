/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:42:47 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/29 11:48:16 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_prepare_builtins(t_struct *mini, char **envp)
{
	t_list	*begin;
	
	(void)envp;
	begin = mini->lst1;
	while (mini->lst1)
	{
		if (mini->lst1->tag == BUILTIN)
		{
			if(ft_strstr(mini->lst1->content, "pwd"))
					ft_pwd();
		}
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
}
