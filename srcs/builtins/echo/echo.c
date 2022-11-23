/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 23:19:49 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/22 23:20:11 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_strstr_echo(char *str, char *cmp)
{
	int	i;

	i = 0;
	while (str[i] == cmp[i] && str[i] && cmp[i])
		i++;
	if (str[i] == '\0' && cmp[i] == '\0')
		return (1);
	else if (cmp[i] == '\0')
	{
		while (str[i] == 'n')
			i++;
		if (str[i] == '\0')
			return (1);
	}
	return (0);
}

static void	print_whithout_lb(char **cmd)
{
	int	i;

	i = 2;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	g_status = 0;
}

static void	print_whith_lb(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
	g_status = 0;
}

void	ft_echo(char **cmd)
{
	if (cmd[1] == NULL)
	{
		printf("\n");
		g_status = 0;
	}
	else if (ft_strstr_echo(cmd[1], "-n"))
		print_whithout_lb(cmd);
	else
		print_whith_lb(cmd);
}
