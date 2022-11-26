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
		check_no_file_or_dir(command);
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
			home = ft_substr((char *)tmp->content, 5, ft_strlen(tmp->content));
			return (home);
		}
		tmp = tmp->next;
	}
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
		if (command == NULL)
			return ;
	}
	update_pwd(mini, command);
}
