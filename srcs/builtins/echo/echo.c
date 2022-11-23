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

static void	print_whithout_lb(t_list *n)
{
	char	*content;

	while (n != NULL)
	{
		content = (char *)n->content;
		printf("%s", content);
		n = n->next;
	}
	g_status = 0;
}

static void	print_whith_lb(t_list *n)
{
	char	*content;

	while (n != NULL)
	{
		content = (char *)n->content;
		printf("%s\n", content);
		n = n->next;
	}
	g_status = 0;
}

void	ft_echo(t_list *n)
{
	if (n == NULL)
	{
		printf("\n");
		g_status = 0;
	}
	else if (ft_strstr_echo(n->content, "-n"))
	{
		n = n->next;
		print_whithout_lb(n);
	}
	else
		print_whith_lb(n);
}
