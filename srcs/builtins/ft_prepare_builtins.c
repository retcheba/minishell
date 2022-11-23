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

void	ft_prepare_builtins(t_struct *mini, char **cmd)
{
	if (ft_strstr(cmd[0], "echo"))
		ft_echo(cmd);
	if (ft_strstr(cmd[0], "pwd"))
		ft_pwd();
	if (ft_strstr(cmd[0], "env"))
		print_env(mini->env);
	if (ft_strstr(cmd[0], "export"))
		check_export_args(mini, cmd);
	if (ft_strstr(cmd[0], "unset"))
		ft_unset(mini, cmd);
	if (ft_strstr(cmd[0], "cd"))
		ft_cd(mini, cmd);
}
