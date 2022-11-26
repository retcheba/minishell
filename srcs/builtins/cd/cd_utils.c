/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 06:30:24 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/26 06:31:17 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_list_cd(t_struct *mini, char *arg)
{
	if (mini->free_list == NULL)
			mini->free_list = new_link(arg, 0);
	else
			mini->free_list = add_link_bottom(mini->free_list, \
				new_link(arg, 0));
}

void	check_no_file_or_dir(char *command)
{
	if (command)
	{
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	g_status = 1;
}

t_list	*update_pwd_in_export_env(t_list *envp, char *pwd)
{
	t_list	*tmp;

	tmp = envp;
	while (envp->next)
	{
		if (ft_strncmp((char *)envp->content, "PWD=", 4) == 0)
		{
			envp->content = pwd;
			break ;
		}
		envp = envp->next;
	}
	envp = tmp;
	return (envp);
}

t_list	*update_oldpwd_in_export_env(t_list *envp, char *oldpwd)
{
	t_list	*tmp;

	tmp = envp;
	while (envp->next)
	{
		if (ft_strncmp((char *)envp->content, "OLDPWD=", 7) == 0)
		{
			envp->content = oldpwd;
			break ;
		}
		envp = envp->next;
	}
	envp = tmp;
	return (envp);
}
