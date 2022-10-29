/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:25:07 by subrandt          #+#    #+#             */
/*   Updated: 2022/10/27 13:24:37 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

//Print the absolute pathname of the current working directory.
//PATH_MAX = 4096 (limits.h)
void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, PATH_MAX);
	printf("%s\n", pwd);
}
