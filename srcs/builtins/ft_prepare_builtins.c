/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:42:47 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/10 16:57:46 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_prepare_builtins(t_struct *mini)
{
	t_list	*begin;

	begin = mini->lst1;
	while (mini->lst1)
	{
		if (mini->lst1->tag == BUILTIN)
		{
			if (ft_strstr(mini->lst1->content, "echo"))
				ft_echo(mini->lst1->next);
			if (ft_strstr(mini->lst1->content, "pwd"))
				ft_pwd();
			if (ft_strstr(mini->lst1->content, "env"))
				print_env(mini->env);
			if (ft_strstr(mini->lst1->content, "export"))
				check_export_args(mini, mini->lst1->next);
			if (ft_strstr(mini->lst1->content, "unset"))
				ft_unset(mini, mini->lst1->next);
		}
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
}
