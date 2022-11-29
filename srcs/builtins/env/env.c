/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:40:11 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/03 17:00:58 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//prints env 
void	print_env(char **cmd, t_list *env)
{
	t_list	*tmp;

	tmp = env;
	if (cmd[1] == NULL)
	{
		while (tmp)
		{
			printf("%s\n", (char *)tmp->content);
			tmp = tmp->next;
		}
		g_status = 0;
	}
	else
	{
		ft_putstr_fd("‘", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		g_status = 127;
	}
}

//creates the env-list
void	ft_init_env(t_struct *mini, char **envp)
{
	int		i;

	i = 0;
	mini->env = NULL;
	while (envp[i])
	{
		if (mini->env == NULL)
			mini->env = new_link(envp[i], 0);
		else
			add_link_bottom(mini->env, new_link(envp[i], 0));
		i++;
	}
}
