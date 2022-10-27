/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_to_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 23:57:34 by retcheba          #+#    #+#             */
/*   Updated: 2022/10/27 00:37:51 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	what_to_execute(t_struct *mini, char **envp)
{
/*
    if (pipe)
        prepare_pipex -> execute_pipex
    else if (builtins)
        prepare_builtins -> execute_builtins
    else if (one cmd)
        prepare_one_cmd -> execute_one_cmd
*/
    ft_prepare_one_cmd(mini, envp);
}
