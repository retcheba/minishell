/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subrandt <subrandt@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 08:25:07 by subrandt          #+#    #+#             */
/*   Updated: 2022/11/03 11:27:44 by subrandt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

//Print the absolute pathname of the current working directory.
//PATH_MAX = 4096 (limits.h)
void	ft_pwd(char *buf)
{
	char	*pwd;

	if (!buf)
		return ;//ft_error
	pwd = getcwd(buf, PATH_MAX);
	printf("%s\n", pwd);
}

int	main(int argc, char **argv)
{
	(void)argc;
	ft_pwd(argv[1]);
	return (0);
}
