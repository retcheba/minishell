/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 05:01:25 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/26 05:01:45 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_free_the_free_list(t_struct *mini)
{
	t_list	*begin;

	begin = mini->free_list;
	while (mini->free_list)
	{
		free(mini->free_list->content);
		mini->free_list = mini->free_list->next;
	}
	mini->free_list = begin;
	ft_free_list(mini->free_list);
}

void	ft_exit(t_struct *mini)
{
	printf ("exit\n");
	free(mini->buff);
	ft_free_tab(mini->tab);
	ft_free_list(mini->lst1);
	ft_free_the_free_list(mini);
	ft_free_list(mini->env);
	ft_free_list(mini->export);
	if (mini->envp != NULL)
		ft_free_tab(mini->envp);
	exit(g_status);
}

int	check_exit_args(t_struct *mini)
{
	if (mini->lst1->next == NULL)
		return (1);
	else if (is_numeric(mini->lst1->next->content))
	{
		if (mini->lst1->next->next != NULL)
		{
			write(2, "exit: too many arguments\n", 25);
			g_status = 1;
		}
		else
		{
			g_status = get_status(ft_atoi(mini->lst1->next->content));
			return (1);
		}
	}
	else
	{
		write(2, "exit: ", 6);
		write(2, mini->lst1->next->content, \
			ft_strlen(mini->lst1->next->content));
		write(2, ": numeric argument required\n", 28);
		g_status = 2;
		return (1);
	}
	return (0);
}
