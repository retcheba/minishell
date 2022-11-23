/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: retcheba <marvin42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 06:51:52 by retcheba          #+#    #+#             */
/*   Updated: 2022/11/20 06:52:22 by retcheba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
