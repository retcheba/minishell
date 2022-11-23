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

#include "../../minishell.h"

static t_list	*update_pwd_in_export_env(t_list *envp, char *pwd)
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

static t_list	*update_oldpwd_in_export_env(t_list *envp, char *oldpwd)
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
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		g_status = 1;
		/* ft_putstr_fd("minishell: cd: HOME not set\n", 2); si unset home */
		return ;
	}
	else
	{
		mini->export = update_oldpwd_in_export_env(mini->export, oldpwd);
		mini->env = update_oldpwd_in_export_env(mini->env, oldpwd);
		getcwd(pwd, PATH_MAX);
		pwd_up = ft_strjoin("PWD=", pwd);
		if (mini->free_list == NULL)
			mini->free_list = new_link(pwd_up, 0);
		else
			mini->free_list = add_link_bottom(mini->free_list, \
				new_link(pwd_up, 0));
		mini->export = update_pwd_in_export_env(mini->export, pwd_up);
		mini->env = update_pwd_in_export_env(mini->env, pwd_up);
		g_status = 0;
	}
}

void	ft_cd(t_struct *mini, char **cmd)
{
	char	*command;
	char	oldpwd[PATH_MAX];

	getcwd(oldpwd, PATH_MAX);
	if (cmd[2] != NULL)
	{
		write(2, "cd: too many arguments\n", 23);
		g_status = 1;
		return ;
	}
	if (cmd[1] == NULL)
		command = "/home"; //pwd donne le PATH /nfs/homes/subrandt
	else
		command = cmd[1];
	update_pwd(mini, command);
}
