/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:58:22 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/25 12:31:33 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	free_list_cd(t_struct *mini, char *arg)
{
	if (mini->free_list == NULL)
			mini->free_list = new_link(arg, 0);
	else
			mini->free_list = add_link_bottom(mini->free_list, \
				new_link(arg, 0));
}

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
		return ;
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	free_list_cd(mini, oldpwd);
	if (chdir(command) == -1)
	{
		if (command)
		{
			ft_putstr_fd(command, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		g_status = 1;
		return ;
	}
	else
	{
		mini->export = update_oldpwd_in_export_env(mini->export, oldpwd);
		mini->env = update_oldpwd_in_export_env(mini->env, oldpwd);
		getcwd(pwd, PATH_MAX);
		pwd_up = ft_strjoin("PWD=", pwd);
		free_list_cd(mini, pwd_up);
		mini->export = update_pwd_in_export_env(mini->export, pwd_up);
		mini->env = update_pwd_in_export_env(mini->env, pwd_up);
		g_status = 0;
	}
}

char	*cd_home(t_list *env)
{
	char	*home;
	t_list	*tmp;

	home = NULL;
	tmp = env;
	while (tmp->next)
	{
		if (ft_strncmp((char *)tmp->content, "HOME=", 5) == 0)
		{
			//printf("tmp->content : %s\n", (char *)tmp->content);
			home = ft_substr((char *)tmp->content, 5, ft_strlen(tmp->content));
			return (home);
		}
		tmp = tmp->next;
	}
	//printf("home : %s\n", home);
	if (home == NULL)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (NULL);
	}
	return ((char *)home);
}

void	ft_cd(t_struct *mini, char **cmd)
{
	char	*command;
	char	*home;
	char	oldpwd[PATH_MAX];

	getcwd(oldpwd, PATH_MAX);
	if (cmd[1] != NULL && cmd[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		g_status = 1;
		return ;
	}
	command = cmd[1];
	if (cmd[1] == NULL)
	{
		home = cd_home(mini->env);
		command = home;
		free_list_cd(mini, home);
		//printf("command : %s\n", command);
		if (command == NULL)
			return ;
	}
	update_pwd(mini, command);
}
