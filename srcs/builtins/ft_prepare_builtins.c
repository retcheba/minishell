/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_builtins.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:42:47 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 04:02:21 by retcheba         ###   ########.fr       */
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
			if (ft_strstr(mini->lst1->content, "pwd"))
				ft_pwd();
			if (ft_strstr(mini->lst1->content, "env"))
				print_env(mini->env);
			if (ft_strstr(mini->lst1->content, "export"))
				print_export(mini->export);
		}
		mini->lst1 = mini->lst1->next;
	}
	mini->lst1 = begin;
}
