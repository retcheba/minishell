/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:40:11 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/06 05:20:39 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
}

int	ft_strstr(char *str, char *to_find)
{
	int	i;

	if (str == NULL || to_find == NULL)
		return (0);
	i = 0;
	while (str[i] && to_find[i] && str[i] == to_find[i])
		i++;
	if (str[i] == '\0' && to_find[i] == '\0')
		return (1);
	return (0);
}

char	*check_empty_dollar(char *result, char *str)
{
	char	*tmp;

	if (str[ft_strlen(str) - 1] == '$')
	{
		tmp = result;
		result = ft_strjoin(result, "$");
		free(tmp);
	}
	return (result);
}

int	is_numeric(char *num)
{
	int	i;

	if (ft_strstr(num, "9223372036854775808")
		|| ft_strstr(num, "-9223372036854775809"))
		return (0);
	i = 0;
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i] >= '0' && num[i] <= '9' && num[i])
		i++;
	if (num[i] == '\0')
		return (1);
	return (0);
}

int	get_status(long long num)
{
	return (num % 255 - num / 255);
}
