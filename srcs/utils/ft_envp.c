/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 01:30:07 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/26 01:30:29 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_envp(t_struct *mini)
{
	t_list	*begin;
	int		i;

	if (mini->envp != NULL)
		ft_free_tab(mini->envp);
	i = 0;
	begin = mini->env;
	while (mini->env)
	{
		i++;
		mini->env = mini->env->next;
	}
	mini->env = begin;
	mini->envp = malloc(sizeof(char *) * (i + 1));
	mini->envp[i] = NULL;
	i = 0;
	while (mini->env)
	{
		mini->envp[i] = ft_strdup(mini->env->content);
		i++;
		mini->env = mini->env->next;
	}
	mini->env = begin;
	return (mini->envp);
}
