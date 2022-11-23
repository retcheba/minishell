/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:58:22 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/22 14:43:25 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	update_pwd_in_export_env(t_list *envp, char *pwd)
{
	t_list	*tmp;

	tmp = envp;
	while (tmp->next)
	{
		if (ft_strncmp((char *)tmp->content, "PWD=", 4) == 0)
		{
			tmp->content = pwd;
			break ;
		}
		tmp = tmp->next;
	}
	envp = tmp;
}

static void	update_oldpwd_in_export_env(t_list *envp, char *oldpwd)
{
	t_list	*tmp;

	tmp = envp;
	while (tmp->next)
	{
		if (ft_strncmp((char *)tmp->content, "OLDPWD=", 7) == 0)
		{
			tmp->content = oldpwd;
			break ;
		}
		tmp = tmp->next;
	}
	envp = tmp;
}

static void	update_pwd(t_struct *mini, char *command)
{
	char	pwd[PATH_MAX];
	char	*pwd_up;
	char	*oldpwd;

	pwd_up = NULL;
	if (getcwd(pwd, PATH_MAX) == NULL)
		return ;//ft_error
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (mini->free_list == NULL)
			mini->free_list = new_link(oldpwd, 0);
	else
			mini->free_list = add_link_bottom(mini->free_list, \
				new_link(oldpwd, 0));
	if (chdir(command) == -1)
	{
		if (command)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		/* ft_putstr_fd("minishell: cd: HOME not set\n", 2); si unset home */
		return ;
	}
	else
	{
		update_oldpwd_in_export_env(mini->export, oldpwd);
		update_oldpwd_in_export_env(mini->env, oldpwd);
		getcwd(pwd, PATH_MAX);
		pwd_up = ft_strjoin("PWD=", pwd);
		if (mini->free_list == NULL)
			mini->free_list = new_link(pwd_up, 0);
		else
			mini->free_list = add_link_bottom(mini->free_list, \
				new_link(pwd_up, 0));
		update_pwd_in_export_env(mini->export, pwd_up);
		update_pwd_in_export_env(mini->env, pwd_up);
	}
}

void	ft_cd(t_struct *mini)
{
	char	*command;
	char	oldpwd[PATH_MAX];

	getcwd(oldpwd, PATH_MAX);
	if (mini->lst1->next == NULL)
		command = "/home"; //pwd donne le PATH /nfs/homes/subrandt
	else
		command = mini->lst1->next->content;
	update_pwd(mini, command);
}
